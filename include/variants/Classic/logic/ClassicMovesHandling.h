#ifndef CLASSICMOVESHANDLING_H
#define CLASSICMOVESHANDLING_H

#include "variants/Classic/data/ClassicMoveConstruct.h"
#include "variants/Classic/data/ClassicGameData.h"

namespace ClassicGameLogic{
    ClassicGameData& appendMove(ClassicGameData& data, const ClassicMoveConstruct& moveData);
    ClassicGameData& undoMove(ClassicGameData& data, std::size_t number);
}

#endif