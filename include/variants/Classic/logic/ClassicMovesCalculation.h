#ifndef CLASSICMOVESCALCULATION_H
#define CLASSICMOVESCALCULATION_H

#include "variants/Classic/data/ClassicGameData.h"
#include "variants/Classic/data/ClassicMoveConstruct.h"

namespace ClassicGameLogic{
    std::unordered_set<ClassicMoveConstruct> getPieceMoves(const ClassicGameData& data, const Position& position);
    std::unordered_set<ClassicMoveConstruct> getLegalMoves(const ClassicGameData& data, Color side);
    std::unordered_set<ClassicMoveConstruct> getLegalMoves(const ClassicGameData& data);
    bool isValidMove(const ClassicGameData& data, const ClassicMoveConstruct& move);
    std::unordered_set<ClassicMoveConstruct> getValidMoves(const ClassicGameData& data);
    std::unordered_set<ClassicMoveConstruct> getValidMoves(const ClassicGameData& data, const Position& position);
}

#endif