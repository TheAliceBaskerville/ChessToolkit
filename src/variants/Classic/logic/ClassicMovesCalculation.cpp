#include "variants/Classic/logic/ClassicMovesCalculation.h"
#include "variants/Classic/logic/ClassicCheckLogic.h"

namespace std {
    template<>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int>& pair) const {
            return std::hash<int>()(pair.first) ^ (std::hash<int>()(pair.second) << 1);
        }
    };
}

namespace {
    std::unordered_set<ClassicMoveConstruct> getDirectionalMoves(const ClassicGameData& data, const Position& position, 
                                                                 const std::unordered_set<std::pair<int, int>>& directions){
        std::unordered_set<ClassicMoveConstruct> moves{};
        int endFile, endRank;
        for (const std::pair<int, int>& direction : directions){
            endFile = static_cast<int>(position.getFile()) + direction.first;
            endRank = static_cast<int>(position.getRank()) + direction.second;
            while(endFile <= static_cast<int>(data.getBoard().getWidth()) && endFile >= 1 &&
                  endRank <= static_cast<int>(data.getBoard().getHeight()) && endRank >= 1){
                Position end{static_cast<std::size_t>(endFile), static_cast<std::size_t>(endRank)};
                if (data.getBoard().isEmpty(end)){
                    moves.insert(ClassicMoveConstruct{position, end});
                    endFile += direction.first;
                    endRank += direction.second;
                }
                else if (data.getBoard().getAt(end).value().getColor() !=
                         data.getBoard().getAt(position).value().getColor()){
                    moves.insert(ClassicMoveConstruct{position, end});
                    break;
                }
                else{
                    break;
                }
            }
        }
        return moves;
    }

    std::unordered_set<ClassicMoveConstruct> getOffsetMoves(const ClassicGameData& data, const Position& position,
                                                            const std::unordered_set<std::pair<int, int>>& offsets){
        std::unordered_set<ClassicMoveConstruct> moves{};
        // TODO: think on formatting here
        int boardWidth{static_cast<int>(data.getBoard().getWidth())};
        int boardHeight{static_cast<int>(data.getBoard().getHeight())};
        int endFile, endRank;
        for (const std::pair<int, int>& offset : offsets){
            endFile = static_cast<int>(position.getFile()) + offset.first;
            endRank = static_cast<int>(position.getRank()) + offset.second;
            if (endFile <= boardWidth && endFile >= 1 && endRank <= boardHeight && endRank >= 1){
                Position end{static_cast<std::size_t>(endFile), static_cast<std::size_t>(endRank)};
                if (data.getBoard().isEmpty(end) || (data.getBoard().getAt(end).value().getColor() != 
                    data.getBoard().getAt(position).value().getColor())){
                    moves.insert(ClassicMoveConstruct{position, end});
                }
            }   
        }
        return moves;
    }

    std::unordered_set<ClassicMoveConstruct> getPawnMoves(const ClassicGameData& data, const Position& position){ // TODO: add support for pawn promotion
        std::unordered_set<ClassicMoveConstruct> moves{};

        std::size_t startingRank, promotionRank;
        int verticalOffsetSign;
        Color opponentColor;
        if (data.getBoard().getAt(position).value().getColor() == Color::WHITE){
            startingRank = 2;
            verticalOffsetSign = 1;
            opponentColor = Color::BLACK;
            promotionRank = data.getBoard().getHeight();
        }
        else{
            startingRank = 7;
            verticalOffsetSign = -1;
            opponentColor = Color::WHITE;
            promotionRank = 1;
        }

        std::function<void(Position)> calculatePromotion = [&](Position end){
            // TODO: think if this list should be in some constant
            for (const PieceType promotionType : {PieceType::BISHOP, PieceType::KNIGHT, PieceType::ROOK, PieceType::QUEEN}){
                Piece promotionChoice = Piece{data.getBoard().getAt(position).value().getColor(), promotionType};
                moves.insert(ClassicMoveConstruct{position, end, promotionChoice});
            }
        };
        // One square move
        if (data.getBoard().isEmpty(position.offset(0, verticalOffsetSign))){
            if (position.offset(0, verticalOffsetSign).getRank() == promotionRank){
                calculatePromotion(position.offset(0, verticalOffsetSign));
            }
            else{
                moves.insert(ClassicMoveConstruct{position, position.offset(0, verticalOffsetSign)});
            }
        }
        // Two square move
        if (position.getRank() == startingRank && data.getBoard().isEmpty(position.offset(0, verticalOffsetSign)) && 
            data.getBoard().isEmpty(position.offset(0, 2 * verticalOffsetSign))){
            moves.insert(ClassicMoveConstruct{position, position.offset(0, 2 * verticalOffsetSign)});
        }

        std::function<void(int)> getCaptureMoves = [&](int fileOffset){
            Position end{position.offset(fileOffset, verticalOffsetSign)};
            if (!data.getBoard().isEmpty(end) &&
                data.getBoard().getAt(end).value().getColor() == opponentColor){
                if (position.offset(fileOffset, verticalOffsetSign).getRank() == promotionRank){
                    calculatePromotion(end);
                }
                else{
                    moves.insert(ClassicMoveConstruct{position, end});
                }
            }
            else if (data.canEnPassant() && data.getEnPassant().value() == end){
                moves.insert(ClassicMoveConstruct{position, end});
            }
        };
        // Capture to the right (from white's perspective)
        if (position.getFile() < data.getBoard().getWidth()){
            getCaptureMoves(1);
        }
        // Capture to the left (from white's perspective)
        if (position.getFile() > 1){
            getCaptureMoves(-1);
        }
        return moves;
    }
}

std::unordered_set<ClassicMoveConstruct> ClassicGameLogic::getPieceMoves(const ClassicGameData& data,
                                                                         const Position& position){
    if (!data.getBoard().isExist(position) || data.getBoard().isEmpty(position)){
        return {};
    }
    switch (data.getBoard().getAt(position).value().getType()){
    case PieceType::PAWN:
        return getPawnMoves(data, position);
    case PieceType::BISHOP:
        return getDirectionalMoves(data, position, {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}});
    case PieceType::ROOK:
        return getDirectionalMoves(data, position, {{1, 0}, {-1, 0}, {0, 1}, {0, -1}});
    case PieceType::QUEEN:
        return getDirectionalMoves(data, position, {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}});
    case PieceType::KING:{
        std::unordered_set<ClassicMoveConstruct> moves{getOffsetMoves(data, position, {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}})};
        std::function<void(std::size_t, Color)> getCastling = [&](std::size_t rank, Color side){
            // Queenside
            if (data.getCastlingRights().at(side, 1)){
                bool flag{true};
                for (std::size_t i{2}; i <= 4; ++i){
                    if (!data.getBoard().isEmpty(Position{i, rank})){
                        flag = false;
                    }
                }
                if (flag){
                    moves.insert(ClassicMoveConstruct{position, Position{3, rank}});
                }
            }
            // Kingside
            else if (data.getCastlingRights().at(side, 8)){
                bool flag{true};
                for (std::size_t i{6}; i <= 7; ++i){
                    if (!data.getBoard().isEmpty(Position{i, rank})){
                        flag = false;
                    }
                }
                if (flag){
                    moves.insert(ClassicMoveConstruct{position, Position{7, rank}});
                }
            }
        };
        if (data.getBoard().getAt(position).value().getColor() == Color::WHITE){
            getCastling(1, Color::WHITE);
        }
        else{
            getCastling(data.getBoard().getHeight(), Color::BLACK);
        }
        return moves;
    }
    case PieceType::KNIGHT:
        return getOffsetMoves(data, position, {{-2, 1}, {-1, 2}, {2, 1}, {1, 2}, {-2, -1}, {-1, -2}, {2, -1}, {1, -2}});
    default:
        throw std::invalid_argument{"Unsupported type of piece"}; // TODO: think when it can happen and what to throw
    }
}

std::unordered_set<ClassicMoveConstruct> ClassicGameLogic::getLegalMoves(const ClassicGameData& data, Color side){
    std::unordered_set<ClassicMoveConstruct> moves{};
    for (std::size_t file{1}; file <= data.getBoard().getWidth(); ++file){
        for(std::size_t rank{1}; rank <= data.getBoard().getHeight(); ++rank){
            if (!data.getBoard().isExist(Position{file, rank}) || data.getBoard().isEmpty(Position{file, rank})){
                continue;
            }
            if (side == Color::BLACK && 
                data.getBoard().getAt(Position{file, rank}).value().getColor() == Color::WHITE){
                continue;
            }
            if (side == Color::WHITE && 
                data.getBoard().getAt(Position{file, rank}).value().getColor() == Color::BLACK){
                continue;
            }
            std::unordered_set<ClassicMoveConstruct> temp{getPieceMoves(data, Position{file, rank})};
            moves.insert(temp.begin(), temp.end());
        }
    }
    return moves;
}

std::unordered_set<ClassicMoveConstruct> ClassicGameLogic::getLegalMoves(const ClassicGameData& data){
    return getLegalMoves(data, data.getCurrentTurn());
}

bool ClassicGameLogic::isValidMove(const ClassicGameData& data, const ClassicMoveConstruct& move){
    if (data.getBoard().isEmpty(move.getStart()) || !data.getBoard().isExist(move.getStart()) ||
        data.getBoard().getAt(move.getStart()).value().getColor() != data.getCurrentTurn()){
        return false;
    }
    std::unordered_set<ClassicMoveConstruct> possibleMoves{getPieceMoves(data, move.getStart())};
    if (possibleMoves.find(move) == possibleMoves.end()){
        return false;
    }
    // TODO: explore other options to do so
    ClassicGameData tempData = data;
    if (move.isPawnPromotion()){
        tempData.accessBoard().setAt(move.getEnd(), move.getPromotionChoice().value());
    }
    else{
        tempData.accessBoard().setAt(move.getEnd(), tempData.getBoard().getAt(move.getStart()).value());
    }
    tempData.accessBoard().clearAt(move.getStart());

    return !isCheck(tempData);
}

std::unordered_set<ClassicMoveConstruct> ClassicGameLogic::getValidMoves(const ClassicGameData& data){
    std::unordered_set<ClassicMoveConstruct> moves{getLegalMoves(data)};
    for (const ClassicMoveConstruct& move : moves){
        // Applying move to see whether it is check after it or not TODO: better comment here
        if (!isValidMove(data, move)){
            moves.erase(move);
        }
    }
    return moves;
}

std::unordered_set<ClassicMoveConstruct> ClassicGameLogic::getValidMoves(const ClassicGameData& data,
                                                                         const Position& position){
    if (!data.getBoard().isExist(position) || data.getBoard().isEmpty(position) ||
        data.getBoard().getAt(position).value().getColor() != data.getCurrentTurn()){
        return {};
    }
    std::unordered_set<ClassicMoveConstruct> moves{getPieceMoves(data, position)};
    for (const ClassicMoveConstruct& move : moves){
        if (!isValidMove(data, move)){
            moves.erase(move);
        }
    }
    return moves;
}