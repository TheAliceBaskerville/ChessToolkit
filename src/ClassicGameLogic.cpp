#include <stdexcept>
#include <cmath> // For std::abs
#include <functional> // For std::function
#include "ClassicGameLogic.h"
#include "ClassicGameData.h"
#include "MoveFactory.h"

ClassicGameLogic::ClassicGameLogic(){}

ClassicGameLogic::~ClassicGameLogic(){}

namespace std {
    template<>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int>& pair) const {
            return std::hash<int>()(pair.first) ^ (std::hash<int>()(pair.second) << 1);
        }
    };
}

namespace {
    std::unordered_set<Move> getDirectionalMoves(IGameData& data, const Position& position, const std::unordered_set<std::pair<int, int>>& directions){
        std::unordered_set<Move> moves{};
        int endFile, endRank;
        for (const std::pair<int, int>& direction : directions){
            endFile = static_cast<int>(position.getFile()) + direction.first;
            endRank = static_cast<int>(position.getRank()) + direction.second;
            while(endFile <= static_cast<int>(data.accessBoard().getWidth()) && endFile >= 1 &&
                  endRank <= static_cast<int>(data.accessBoard().getHeight()) && endRank >= 1){
                Position end{static_cast<std::size_t>(endFile), static_cast<std::size_t>(endRank)};
                if (data.accessBoard().isEmpty(end)){
                    moves.insert(MoveFactory::make(position, end, data));
                    endFile += direction.first;
                    endRank += direction.second;
                }
                else{
                    if (data.accessBoard().getAt(end).value().getColor() !=
                        data.accessBoard().getAt(position).value().getColor()){
                        moves.insert(MoveFactory::make(position, end, data));
                    }
                    break;
                }
            }
        }
        return moves;
    }

    std::unordered_set<Move> getOffsetMoves(IGameData& data, const Position& position, const std::unordered_set<std::pair<int, int>>& offsets){
        std::unordered_set<Move> moves{};
        int endFile, endRank;
        for (const std::pair<int, int>& offset : offsets){
            endFile = static_cast<int>(position.getFile()) + offset.first;
            endRank = static_cast<int>(position.getRank()) + offset.second;
            if(endFile <= static_cast<int>(data.accessBoard().getWidth()) && endFile >= 1 &&
               endRank <= static_cast<int>(data.accessBoard().getHeight()) && endRank >= 1){
                Position end{static_cast<std::size_t>(endFile), static_cast<std::size_t>(endRank)};
                if (data.accessBoard().isEmpty(end) || (data.accessBoard().getAt(end).value().getColor() != 
                    data.accessBoard().getAt(position).value().getColor())){
                    moves.insert(MoveFactory::make(position, end, data));
                }
            }   
        }
        return moves;
    }

    std::unordered_set<Move> getPawnMoves(IGameData& data, const Position& position){ // TODO: add support for pawn promotion
        std::unordered_set<Move> moves{};
        std::size_t startingRank, promotionRank;
        int verticalOffsetSign;
        Color opponentColor;
        if (data.accessBoard().getAt(position).value().getColor() == Color::WHITE){
            startingRank = 2;
            verticalOffsetSign = 1;
            opponentColor = Color::BLACK;
            promotionRank = data.accessBoard().getHeight();
        }
        else{
            startingRank = 7;
            verticalOffsetSign = -1;
            opponentColor = Color::WHITE;
            promotionRank = 1;
        }
        // One square move
        if (data.accessBoard().isEmpty(position.offset(0, verticalOffsetSign))){
            if (position.offset(0, verticalOffsetSign).getRank() == promotionRank){
                // TODO: think if this list should be in some constant
                for (const PieceType promotionOption : {PieceType::BISHOP, PieceType::KNIGHT, PieceType::ROOK, PieceType::QUEEN}){
                    moves.insert(MoveFactory::make(position, position.offset(0, verticalOffsetSign), data, 
                                 Piece{data.accessBoard().getAt(position).value().getColor(), promotionOption}));
                }
            }
            else{
                moves.insert(MoveFactory::make(position, position.offset(0, verticalOffsetSign), data));
            }
        }
        // Two square move
        if (position.getRank() == startingRank && data.accessBoard().isEmpty(position.offset(0, verticalOffsetSign)) && 
            data.accessBoard().isEmpty(position.offset(0, 2 * verticalOffsetSign))){
            moves.insert(MoveFactory::make(position, position.offset(0, 2 * verticalOffsetSign), data));
        }
        ClassicGameData* classicData = dynamic_cast<ClassicGameData*>(&data);
        std::function<void(int)> getCaptureMoves = [&](int fileOffset){
            Position end{position.offset(fileOffset, verticalOffsetSign)};
            if (!data.accessBoard().isEmpty(end) &&
                data.accessBoard().getAt(end).value().getColor() == opponentColor){
                moves.insert(MoveFactory::make(position, end, data));
            }
            else if (classicData->canEnPassant() && classicData->getEnPassant().value() == end){
                moves.insert(MoveFactory::make(position, end, data));
            }
        };
        // Capture to the right (from white's perspective)
        if (position.getFile() < data.accessBoard().getWidth()){
            getCaptureMoves(1);
        }
        // Capture to the left (from white's perspective)
        if (position.getFile() > 1){
            getCaptureMoves(-1);
        }
        return moves;
    }
};

std::unordered_set<Move> ClassicGameLogic::getPieceMoves(IGameData& data, const Position& position) const{
    if (!data.accessBoard().isExist(position)){
        throw std::out_of_range{"Given square does not exist."}; // TODO: better error message
    }
    if (data.accessBoard().isEmpty(position)){
        return {};
    }
    switch (data.accessBoard().getAt(position).value().getType()){
    case PieceType::PAWN:
        return getPawnMoves(data, position);
    case PieceType::BISHOP:
        return getDirectionalMoves(data, position, {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}});
    case PieceType::ROOK:
        return getDirectionalMoves(data, position, {{1, 0}, {-1, 0}, {0, 1}, {0, -1}});
    case PieceType::QUEEN:
        return getDirectionalMoves(data, position, {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}});
    case PieceType::KING:{
        std::unordered_set<Move> moves{getOffsetMoves(data, position, {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}})};
        const ClassicGameData* classicData = dynamic_cast<const ClassicGameData*>(&data);
        std::function<void(std::size_t, Color)> getCastling = [&](std::size_t rank, Color side){
            // Queenside
            if (classicData->getCastlingRights().at(side, 1)){
                bool flag{true};
                for (std::size_t i{2}; i <= 4; ++i){
                    if (!data.accessBoard().isEmpty(Position{i, rank})){
                        flag = false;
                    }
                }
                if (flag){
                    moves.insert(MoveFactory::make(position, Position{3, rank}, data));
                }
            }
            // Kingside
            else if (classicData->getCastlingRights().at(side, 8)){
                bool flag{true};
                for (std::size_t i{6}; i <= 7; ++i){
                    if (!data.accessBoard().isEmpty(Position{i, rank})){
                        flag = false;
                    }
                }
                if (flag){
                    moves.insert(MoveFactory::make(position, Position{7, rank}, data));
                }
            }
        };
        if (data.accessBoard().getAt(position).value().getColor() == Color::WHITE){
            getCastling(1, Color::WHITE);
        }
        else{
            getCastling(data.accessBoard().getHeight(), Color::BLACK);
        }
        return moves;
    }
    case PieceType::KNIGHT:
        return getOffsetMoves(data, position, {{-2, 1}, {-1, 2}, {2, 1}, {1, 2}, {-2, -1}, {-1, -2}, {2, -1}, {1, -2}});
    default:
        throw std::invalid_argument{"Unsupported type of piece"}; // TODO: think when it can happen and what to throw
    }
}

ChessVariant ClassicGameLogic::getVariant() const{
    return variant;
}

std::unordered_set<Move> ClassicGameLogic::getLegalMoves(IGameData& data, Color side) const{
    std::unordered_set<Move> moves{};
    for (std::size_t file{1}; file <= data.accessBoard().getWidth(); ++file){
        for(std::size_t rank{1}; rank <= data.accessBoard().getHeight(); ++rank){
            if (!data.accessBoard().isExist(Position{file, rank}) || data.accessBoard().isEmpty(Position{file, rank})){
                continue;
            }
            if (side == Color::BLACK && 
                data.accessBoard().getAt(Position{file, rank}).value().getColor() == Color::WHITE){
                continue;
            }
            if (side == Color::WHITE && 
                data.accessBoard().getAt(Position{file, rank}).value().getColor() == Color::BLACK){
                continue;
            }
            std::unordered_set<Move> temp{getPieceMoves(data, Position{file, rank})};
            moves.insert(temp.begin(), temp.end());
        }
    }
    return moves;
}

std::unordered_set<Move> ClassicGameLogic::getLegalMoves(IGameData& data) const{
    return getLegalMoves(data, data.getCurrentTurn());
}

bool ClassicGameLogic::isValidMove(IGameData& data, const Move& move) const{
    return (getValidMoves(data, move.getStart()).count(move) != 0);
}

std::unordered_set<Move> ClassicGameLogic::getValidMoves(IGameData& data) const{
    std::unordered_set<Move> moves{getLegalMoves(data)};
    for (const Move& move : moves){
        makeMove(data, move);
        Color originSide{Color::WHITE};
        if (data.getCurrentTurn() == Color::WHITE){
            originSide = Color::BLACK;
        }
        if (isCheck(data, originSide)){
            moves.erase(move);
        }
        undoMove(data);
    }
    return moves;
}

std::unordered_set<Move> ClassicGameLogic::getValidMoves(IGameData& data, const Position& position) const{
    std::unordered_set<Move> moves{getPieceMoves(data, position)};
    for (const Move& move : moves){
        makeMove(data, move);
        Color originSide{Color::WHITE};
        if (data.getCurrentTurn() == Color::WHITE){
            originSide = Color::BLACK;
        }
        if (isCheck(data, originSide)){
            moves.erase(move);
        }
        undoMove(data);
    }
    return moves;
}

bool ClassicGameLogic::isUnderAttack(IGameData& data, const Position& position, Color side) const{ // TODO: think on code duplication
    std::unordered_set<Move> opponentMoves;
    if (side == Color::BLACK){
        opponentMoves = getLegalMoves(data, Color::WHITE);
    }
    else{
        opponentMoves = getLegalMoves(data, Color::BLACK);
    }
    for (const Move& move : opponentMoves){
        if (move.getEnd() == position){
            return true;
        }
    }
    return false;
}

bool ClassicGameLogic::isUnderAttack(IGameData& data, const Position& position) const{
    return isUnderAttack(data, position, data.getCurrentTurn());
}

bool ClassicGameLogic::isCheck(IGameData& data, Color side) const{
    ClassicGameData* classicData = dynamic_cast<ClassicGameData*>(&data);
    if (side == Color::BLACK){
        return isUnderAttack(data, classicData->getKingPosition(Color::BLACK));
    }
    else{
        return isUnderAttack(data, classicData->getKingPosition(Color::WHITE));
    }
}

bool ClassicGameLogic::isCheck(IGameData& data) const{
    return isCheck(data, data.getCurrentTurn());
}

GameStatus ClassicGameLogic::getStatus(IGameData& data) const{
    if (getValidMoves(data).size() == 0){
        if (isCheck(data)){
            return GameStatus{DetailedStatus::CHECKMATE};
        }
        else{
            return GameStatus{DetailedStatus::STALEMATE};
        }
    }
    // History stores halfmoves so to apply 50-moves rule we need at least 100 of them being stored.
    constexpr std::size_t FiftyMoveRuleThreshold = 100;
    if (data.getHistory().size() > FiftyMoveRuleThreshold){
        std::size_t movesWithoutPawn{0}, movesWithoutCapture{0};
        for (const Move& move : data.getHistory()){
            if (move.getMovedPiece().value().getType() == PieceType::PAWN){
                movesWithoutPawn = 0;
            }
            else{
                ++movesWithoutPawn;
            }
            if (movesWithoutPawn >= FiftyMoveRuleThreshold){ // TODO: Check if this should include edge case 100
                return GameStatus{DetailedStatus::FIFTY_MOVES_RULE};
            }
            if (move.isCapture()){
                movesWithoutCapture = 0;
            }
            else{
                ++movesWithoutCapture;
            }
            if (movesWithoutCapture >= FiftyMoveRuleThreshold){ // TODO: Check if this should include edge case 100
                return GameStatus{DetailedStatus::FIFTY_MOVES_RULE};
            }
        }
    }
    // TODO: implement checking for insufficient materials and threefold repetition rules.
    return GameStatus{DetailedStatus::ONGOING};
}

IGameData& ClassicGameLogic::makeMove(IGameData& data, const Move& move) const{
    Piece movedPiece{move.getMovedPiece().value()};
    data.accessBoard().clearAt(move.getStart());

    if (move.isPawnPromotion()){
        data.accessBoard().setAt(move.getEnd(), move.getPromotionChoice().value());
    }
    else{
        data.accessBoard().setAt(move.getEnd(), movedPiece);
    }

    if (move.isEnPassant()){
        if (movedPiece.getColor() == Color::WHITE){
            data.accessBoard().clearAt(move.getEnd().offset(0, -1));
        }
        else{
            data.accessBoard().clearAt(move.getEnd().offset(0, 1));
        }
    }

    data.appendHistory(move);

    if (data.getCurrentTurn() == Color::WHITE){
        data.setCurrentTurn(Color::BLACK);
    }
    else{
        data.setCurrentTurn(Color::WHITE);
    }
    
    ClassicGameData* classicData = dynamic_cast<ClassicGameData*>(&data);
    if (move.isCastling()){
        // White queenside
        if (move.getEnd() == Position{3, 1}){
            // Removing rock from it's origin position
            data.accessBoard().clearAt(Position{1, 1});
            // Setting rock to it's new position
            data.accessBoard().setAt(Position{4, 1}, Piece{Color::WHITE, PieceType::ROOK});
        }
        // White kingside
        else if (move.getEnd() == Position{7, 1}){
            // Removing rock from it's origin position
            data.accessBoard().clearAt(Position{8, 1});
            // Setting rock to it's new position
            data.accessBoard().setAt(Position{6, 1}, Piece{Color::WHITE, PieceType::ROOK});
        }
        // Black queenside
        else if (move.getEnd() == Position{3, 8}){
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
        classicData->setKingPosition(movedPiece.getColor(), move.getEnd());
    }
    else if (movedPiece.getType() == PieceType::PAWN){
        std::size_t startRank{move.getStart().getRank()}, endRank{move.getEnd().getRank()};
        if ((startRank > endRank && startRank - endRank == 2) || (startRank < endRank && endRank - startRank == 2)){
            if (movedPiece.getColor() == Color::BLACK){
                classicData->setEnPassant(move.getStart().offset(0, -1));
            }
            else{
                classicData->setEnPassant(move.getStart().offset(0, 1));
            }
        }
    }
    else{
        classicData->clearEnPassant();
    }
    for (std::size_t file : move.getCastlingRemovals()){
        classicData->removeCastling(movedPiece.getColor(), file);
    }
    return data;
}

IGameData& ClassicGameLogic::undoMove(IGameData& data, std::size_t number) const{
    if (data.getHistory().size() == 0){
        return data;
    }
    if (number > data.getHistory().size()){
        number = data.getHistory().size();
    }
    for (std::size_t i{0}; i < number; ++i){
        Move move = data.popHistory();
        Piece movedPiece{move.getMovedPiece().value()};
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

        if (data.getCurrentTurn() == Color::WHITE){
            data.setCurrentTurn(Color::BLACK);
        }
        else{
            data.setCurrentTurn(Color::WHITE);
        }

        ClassicGameData* classicData = dynamic_cast<ClassicGameData*>(&data);
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
            classicData->setKingPosition(movedPiece.getColor(), move.getStart());
        }
        if (classicData->getHistory().size() > 0){
            const Move& previousMove{classicData->getHistory().back()};
            if (previousMove.getMovedPiece().value().getType() == PieceType::PAWN){
                std::size_t startRank{previousMove.getStart().getRank()}, endRank{previousMove.getEnd().getRank()};
                if ((startRank > endRank && startRank - endRank == 2) || 
                    (startRank < endRank && endRank - startRank == 2)){
                    if (previousMove.getMovedPiece().value().getColor() == Color::BLACK){
                        classicData->setEnPassant(previousMove.getStart().offset(0, -1));
                    }
                    else{
                        classicData->setEnPassant(previousMove.getStart().offset(0, 1));
                    }
                }
            } 
                
        }
        for (std::size_t file : move.getCastlingRemovals()){
            classicData->addCastling(movedPiece.getColor(), file);
        }
    }
    return data;
}

std::unique_ptr<IGameLogic> ClassicGameLogic::clone() const{
    return std::make_unique<ClassicGameLogic>();
}