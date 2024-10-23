#include <stdexcept>
#include <functional> // For std::function
#include <cctype> // For std::tolower
#include <sstream>
#include "variants/Classic/logic/ClassicGameLogic.h"
#include "FileConverter.h"

ClassicGameData& ClassicGameLogic::appendMove(ClassicGameData& data, const ClassicMoveConstruct& moveData){
    if (!isValidMove(data, moveData)){
        return data;
    }///
    Position start{moveData.getStart()}, end{moveData.getEnd()};
    std::optional<Piece> promotionChoice{moveData.getPromotionChoice()};
    Piece movedPiece{data.getBoard().getAt(start).value()}; // TODO: think if checking for value here is needed
    std::optional<Piece> capturedPiece{data.getBoard().getAt(end)};
    bool isCapture{capturedPiece.has_value()};

    bool isPawnPromotion{false};
    if (movedPiece.getType() == PieceType::PAWN && 
       ((movedPiece.getColor() == Color::WHITE && end.getRank() == data.getBoard().getHeight()) ||
       (movedPiece.getColor() == Color::BLACK && end.getRank() == 1))){
        isPawnPromotion = true;
        if (!promotionChoice.has_value()){
            // TODO: better error message
            throw std::invalid_argument{"Move is promotion, but promotionChoice = std::nullopt is given."};
        }
    }
    else{
        // TODO: think on whether promotionChoice validation here is needed or I could just set it to std::nullopt
    }
    bool isEnPassant{false};
    if (data.canEnPassant() && end == data.getEnPassant().value()){
        isEnPassant = true;
        // TODO: think on early return here
    }
    bool isCastling{false};
    std::unordered_set<std::size_t> castlingRemovals{};
    if (movedPiece.getType() == PieceType::KING){
        std::function<void(std::size_t, Color)> checkCastling = [&](std::size_t rank, Color side){
            // TODO: think if it is possible to avoid reusing this code, as it is used in getLegalMoves()
            // Queenside
            if (end == Position{3, rank} && data.getCastlingRights().at(side, 1)){
                bool flag{true};
                for (std::size_t i{2}; i <= 4; ++i){
                    if (!data.getBoard().isEmpty(Position{i, rank})){
                        flag = false;
                    }
                }
                if (flag){
                    isCastling = true;
                }
            }
            // Kingside
            else if (end == Position{7, rank} && data.getCastlingRights().at(side, 8)){
                bool flag{true};
                for (std::size_t i{6}; i <= 7; ++i){
                    if (!data.getBoard().isEmpty(Position{i, rank})){
                        flag = false;
                    }
                }
                if (flag){
                    isCastling = true;
                }
            }
        };
        if (movedPiece.getColor() == Color::WHITE){
            checkCastling(1, Color::WHITE);
        }
        else{
            checkCastling(data.getBoard().getHeight(), Color::BLACK);
        }
        for (std::size_t file : data.getCastlingRights().get(movedPiece.getColor())){
            castlingRemovals.insert(file);
        }
    }
    else if (movedPiece.getType() == PieceType::ROOK && 
             data.getCastlingRights().at(movedPiece.getColor(), start.getFile())){
        castlingRemovals.insert(start.getFile());
    }

    /*
        After defining basic properties of move, in order to create a notation for it, status evaluation is needed,
        which implies game state is already updated according to a given move.
    */
    data.accessBoard().clearAt(start);

    if (isPawnPromotion){
        data.accessBoard().setAt(end, promotionChoice.value());
    }
    else{
        data.accessBoard().setAt(end, movedPiece);
    }

    if (isEnPassant){
        if (movedPiece.getColor() == Color::WHITE){
            data.accessBoard().clearAt(end.offset(0, -1));
        }
        else{
            data.accessBoard().clearAt(end.offset(0, 1));
        }
    }

    data.setCurrentTurn(switchColor(data.getCurrentTurn()));
    
    if (isCastling){
        // White queenside
        if (end == Position{3, 1}){
            // Removing rock from it's origin position
            data.accessBoard().clearAt(Position{1, 1});
            // Setting rock to it's new position
            data.accessBoard().setAt(Position{4, 1}, Piece{Color::WHITE, PieceType::ROOK});
        }
        // White kingside
        else if (end == Position{7, 1}){
            // Removing rock from it's origin position
            data.accessBoard().clearAt(Position{8, 1});
            // Setting rock to it's new position
            data.accessBoard().setAt(Position{6, 1}, Piece{Color::WHITE, PieceType::ROOK});
        }
        // Black queenside
        else if (end == Position{3, 8}){
            // Removing rock from it's origin position
            data.accessBoard().clearAt(Position{1, 8});
            // Setting rock to it's new position
            data.accessBoard().setAt(Position{4, 8}, Piece{Color::BLACK, PieceType::ROOK});
        }
        // Black kingside
        else{
            // Removing rock from it's origin position
            data.accessBoard().clearAt(Position{8, 8});
            // Setting rock to it's new position
            data.accessBoard().setAt(Position{6, 8}, Piece{Color::BLACK, PieceType::ROOK});
        }
    }
    if (movedPiece.getType() == PieceType::KING){
        data.setKingPosition(movedPiece.getColor(), end);
    }
    else if (movedPiece.getType() == PieceType::PAWN){
        std::size_t startRank{start.getRank()}, endRank{end.getRank()};
        if ((startRank > endRank && startRank - endRank == 2) || (startRank < endRank && endRank - startRank == 2)){
            if (movedPiece.getColor() == Color::BLACK){
                data.setEnPassant(start.offset(0, -1));
            }
            else{
                data.setEnPassant(start.offset(0, 1));
            }
        }
    }
    else{
        data.clearEnPassant();
    }
    for (std::size_t file : castlingRemovals){
        data.removeCastling(movedPiece.getColor(), file);
    }
    
    bool isCheck{ClassicGameLogic::isCheck(data)};
    // TODO: think on adding check for isCheck before calling getStatus()
    bool isCheckmate{ClassicGameLogic::getStatus(data).getDetailedType() == DetailedStatus::CHECKMATE};

    std::string notation;
    if (isCastling){
        // Kingside
        if (end.getFile() == 7){
            notation = "0-0";
        }
        // Queenside
        else{
            notation = "0-0-0";
        }
    }
    else if (isPawnPromotion){
        notation = fileToChar(end.getFile()) + std::to_string(end.getRank()) + '=';
        switch (promotionChoice.value().getType()){
        case PieceType::BISHOP: notation.push_back('B'); break;
        case PieceType::KNIGHT: notation.push_back('N'); break;
        case PieceType::ROOK:   notation.push_back('R'); break;
        case PieceType::QUEEN:  notation.push_back('Q'); break;
        default:
            throw std::invalid_argument{"Unexpected promotion choice."}; // TODO: better error message + think whether this validation should be done earlier
        }
    }
    else if (movedPiece.getType() == PieceType::PAWN){
        if (isCapture){
            notation = fileToChar(start.getFile()) + "x" + fileToChar(end.getFile()) + std::to_string(end.getRank());
        }
        else{
            notation = fileToChar(end.getFile()) + std::to_string(end.getRank());
        }
    }
    else{
        switch (movedPiece.getType()){
        case PieceType::BISHOP: notation = 'B'; break;
        case PieceType::KNIGHT: notation = 'N'; break;
        case PieceType::ROOK:   notation = 'R'; break;
        case PieceType::QUEEN:  notation = 'Q'; break;
        case PieceType::KING:   notation = 'K'; break;
        default:
            throw std::invalid_argument{"Unexpected moved piece type."}; // TODO: better error message + think when it can happen
        }
        if (isCapture){
            notation.push_back('x');
        }
        notation += fileToChar(end.getFile()) + std::to_string(end.getRank());
    }
    if (isCheckmate){
        notation.push_back('#');
    }
    else if (isCheck){
        notation.push_back('+');
    }    

    ClassicMove move{start, end, movedPiece, capturedPiece, isEnPassant, isPawnPromotion, isCastling, promotionChoice,
                     castlingRemovals, isCheck, isCheckmate, notation};

    data.appendHistory(ClassicMoveRecord{move, data.toFEN()});
    return data;
}

ClassicGameData& ClassicGameLogic::undoMove(ClassicGameData& data, std::size_t number){
    if (data.getHistory().size() == 0){
        return data;
    }
    if (number > data.getHistory().size()){
        number = data.getHistory().size();
    }
    for (std::size_t i{0}; i < number; ++i){
        ClassicMove move = data.popHistory().getMove();
        Piece movedPiece{move.getMovedPiece()};
        if (move.isPawnPromotion()){
            data.accessBoard().setAt(move.getStart(), Piece{movedPiece.getColor(), PieceType::PAWN});
        }
        else{
            data.accessBoard().setAt(move.getStart(), movedPiece);
        }

        if (move.isCapture()){
            data.accessBoard().setAt(move.getEnd(), move.getCapturedPiece().value());
        }
        else{
            data.accessBoard().clearAt(move.getEnd());
        }

        if (move.isEnPassant()){
            if (movedPiece.getColor() == Color::WHITE){
                data.accessBoard().setAt(move.getEnd().offset(0, -1), Piece{Color::BLACK, PieceType::PAWN});
            }
            else{
                data.accessBoard().setAt(move.getEnd().offset(0, 1), Piece{Color::WHITE, PieceType::PAWN});
            }
        }

        data.setCurrentTurn(switchColor(data.getCurrentTurn()));

        if (move.isCastling()){
            // White queenside
            if (move.getEnd() == Position{3, 1}){
                // Setting rock to it's origin position
                data.accessBoard().setAt(Position{1, 1}, Piece{Color::WHITE, PieceType::ROOK});
                // Removing rock from it's new position
                data.accessBoard().clearAt(Position{4, 1});
            }
            // White kingside
            else if (move.getEnd() == Position{7, 1}){
                // Setting rock to it's origin position
                data.accessBoard().setAt(Position{8, 1}, Piece{Color::WHITE, PieceType::ROOK});
                // Removing rock from it's new position
                data.accessBoard().clearAt(Position{6, 1});
            }
            // Black queenside
            else if (move.getEnd() == Position{3, 8}){
                // Setting rock to it's origin position
                data.accessBoard().setAt(Position{1, 8}, Piece{Color::BLACK, PieceType::ROOK});
                // Removing rock from it's new position
                data.accessBoard().clearAt(Position{4, 8});
            }
            // Black kingside
            else{
                // Setting rock to it's origin position
                data.accessBoard().setAt(Position{8, 8}, Piece{Color::BLACK, PieceType::ROOK});
                // Removing rock from it's new position
                data.accessBoard().clearAt(Position{6, 8});
            }
        }
        if (movedPiece.getType() == PieceType::KING){
            data.setKingPosition(movedPiece.getColor(), move.getStart());
        }
        if (data.getHistory().size() > 0){
            const ClassicMove& previousMove{data.getHistory().back().getMove()};
            if (previousMove.getMovedPiece().getType() == PieceType::PAWN){
                std::size_t startRank{previousMove.getStart().getRank()}, endRank{previousMove.getEnd().getRank()};
                if ((startRank > endRank && startRank - endRank == 2) || 
                    (startRank < endRank && endRank - startRank == 2)){
                    if (previousMove.getMovedPiece().getColor() == Color::BLACK){
                        data.setEnPassant(previousMove.getStart().offset(0, -1));
                    }
                    else{
                        data.setEnPassant(previousMove.getStart().offset(0, 1));
                    }
                }
            } 
                
        }
        for (std::size_t file : move.getCastlingRemovals()){
            data.addCastling(movedPiece.getColor(), file);
        }
    }
    return data;
}