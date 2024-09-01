#ifndef MOVEFACTORY_H
#define MOVEFACTORY_H

#include "Position.h"
#include "Move.h"
#include "ChessGame.h"

class IGameData;

// Refactor using templates
class MoveFactory{ // TODO: think on makeMove()
public:
    // TODO: rethink move and update to accept interface instead of downcasting to concrete implementation
    static Move make(const Position& start, const Position& end, const IGameData& data,
                     const std::optional<Piece>& promotionChoice=std::nullopt);

    static Move make(const Position& start, const Position& end, const ChessGame& game,
                     const std::optional<Piece>& promotionChoice=std::nullopt);
};

#endif