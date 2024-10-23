#ifndef CLASSICSTATUSGENERATION_H
#define CLASSICSTATUSGENERATION_H

#include "GameStatus.h"
#include "variants/Classic/data/ClassicGameData.h"

namespace ClassicGameLogic{
    GameStatus getStatus(const ClassicGameData& data);
}

#endif