#ifndef CLASSICCHECKLOGIC_H
#define CLASSICCHECKLOGIC_H

#include "variants/Classic/data/ClassicGameData.h"

namespace ClassicGameLogic{
    bool isUnderAttack(const ClassicGameData& data, const Position& position, Color side);
    bool isUnderAttack(const ClassicGameData& data, const Position& position);

    bool isCheck(const ClassicGameData& data, Color side);
    bool isCheck(const ClassicGameData& data);
}

#endif