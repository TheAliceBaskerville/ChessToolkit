#include "variants/Classic/logic/ClassicCheckLogic.h"
#include "variants/Classic/logic/ClassicMovesCalculation.h"

bool ClassicGameLogic::isUnderAttack(const ClassicGameData& data, const Position& position, Color side){
    std::unordered_set<ClassicMoveConstruct> opponentMoves{getLegalMoves(data, switchColor(side))};
    for (const ClassicMoveConstruct& move : opponentMoves){
        if (move.getEnd() == position){
            return true;
        }
    }
    return false;
}

bool ClassicGameLogic::isUnderAttack(const ClassicGameData& data, const Position& position){
    return isUnderAttack(data, position, data.getCurrentTurn());
}

bool ClassicGameLogic::isCheck(const ClassicGameData& data, Color side){
    return isUnderAttack(data, data.getKingPosition(side), side);
}

bool ClassicGameLogic::isCheck(const ClassicGameData& data){
    return isCheck(data, data.getCurrentTurn());
}