#include "variants/Classic/logic/ClassicStatusGeneration.h"
#include "variants/Classic/logic/ClassicMovesCalculation.h"
#include "variants/Classic/logic/ClassicCheckLogic.h"

namespace{
    bool checkFiftyMoveRule(const ClassicGameData& data){
        // History stores halfmoves so to apply 50-moves rule we need at least 100 of them being stored.
        constexpr std::size_t FiftyMoveRuleThreshold = 100;
        if (data.getHistory().size() > FiftyMoveRuleThreshold){
            std::size_t movesWithoutPawn{0}, movesWithoutCapture{0};
            for (const ClassicMoveRecord& moveRecord : data.getHistory()){
                ClassicMove move{moveRecord.getMove()};
                if (move.getMovedPiece().getType() == PieceType::PAWN){
                    movesWithoutPawn = 0;
                }
                else{
                    ++movesWithoutPawn;
                }
                if (movesWithoutPawn >= FiftyMoveRuleThreshold){ // TODO: Check if this should include edge case 100
                    return true;
                }
                if (move.isCapture()){
                    movesWithoutCapture = 0;
                }
                else{
                    ++movesWithoutCapture;
                }
                if (movesWithoutCapture >= FiftyMoveRuleThreshold){ // TODO: Check if this should include edge case 100
                    return true;
                }
            }
        }
        return false;
    }

    bool isIrreversibleMove(const ClassicMove& move){
        return (move.isCapture() || move.isCastling() || move.getMovedPiece().getType() == PieceType::PAWN);
    }

    std::string stripMoveCounters(const FEN& fen){
        std::string fenStr{fen.str()};
        std::size_t lastSpaceIndex = fenStr.find_last_of(' ');
        std::size_t secondLastSpaceIndex = fenStr.find_last_of(' ', lastSpaceIndex - 1);
        return fenStr.substr(0, secondLastSpaceIndex);
    }

    bool comparePositions(const FEN& left, const FEN& right){
        return (stripMoveCounters(left) == stripMoveCounters(right));
    }

    bool checkThreefoldRepetition(const ClassicGameData& data){
        FEN currentPositionFEN{data.toFEN()};
        std::size_t count{1};
        for (const ClassicMoveRecord& moveRecord : data.getHistory()){
            if (isIrreversibleMove(moveRecord.getMove())){
                return false;
            }
            if (comparePositions(currentPositionFEN, moveRecord.getFEN())){
                ++count;
            }
            if (count == 3){
                return true;
            }
        }
        return false;
    }

    bool checkInsufficientMaterial(const ClassicGameData& data){
        std::unordered_map<PieceType, std::size_t> piecesCount;
        std::size_t bishopsOnWhiteSquares{0}, bishopsOnBlackSquares{0};

        std::optional<Piece> currentPiece;
        for (std::size_t file{1}; file <= data.getBoard().getWidth(); ++file){
            for (std::size_t rank{1}; rank <= data.getBoard().getHeight(); ++rank){
                currentPiece = data.getBoard().getAt(Position{file, rank});
                if (currentPiece){
                    PieceType type = currentPiece.value().getType();
                    if (type == PieceType::QUEEN || type == PieceType::ROOK){
                        return false;
                    }
                    if (type == PieceType::BISHOP){
                        if ((file + rank) % 2 == 0){
                            ++bishopsOnWhiteSquares;
                        }
                        else{
                            ++bishopsOnBlackSquares;
                        }
                        ++piecesCount[type];
                    }
                    else if (type != PieceType::KING){
                        ++piecesCount[type];
                    }
                }
            }
        }

        // Check for King vs. King
        if (piecesCount.size() == 0) {
            return true;
        }

        // Check for King + Knight vs. King
        if (piecesCount.size() == 1 && piecesCount[PieceType::KNIGHT] == 1){
            return true;
        }

        // Check for King + Bishop vs. King
        if (piecesCount.size() == 1 && piecesCount[PieceType::BISHOP] == 1){
            return true;
        }

        // Check for King + Bishops vs. King + Bishops on same-colored squares
        if (piecesCount.size() == 1 && piecesCount[PieceType::BISHOP] > 1){
            return ((bishopsOnBlackSquares > 0 && bishopsOnWhiteSquares == 0) ||
                    (bishopsOnWhiteSquares > 0 && bishopsOnBlackSquares == 0));
        }

        return false;
    }
}

GameStatus ClassicGameLogic::getStatus(const ClassicGameData& data){
    if (getValidMoves(data).size() == 0){
        if (isCheck(data)){
            return GameStatus{DetailedStatus::CHECKMATE};
        }
        else{
            return GameStatus{DetailedStatus::STALEMATE};
        }
    }
    if (checkInsufficientMaterial(data)){
        return GameStatus{DetailedStatus::INSUFFICIENT_MATERIAL};
    }
    if (checkThreefoldRepetition(data)){
        return GameStatus{DetailedStatus::THREEFOLD_REPETITION};
    }
    if (checkFiftyMoveRule(data)){
        return GameStatus{DetailedStatus::FIFTY_MOVES_RULE};
    }
    return GameStatus{DetailedStatus::ONGOING};
}