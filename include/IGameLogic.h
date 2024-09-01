#ifndef IGAMELOGIC_H
#define IGAMELOGIC_H

#include <unordered_set>
#include "ChessVariant.h"
#include "IGameData.h"
#include "GameStatus.h"

class IGameLogic{
public:
    virtual ~IGameLogic() = default;

    virtual ChessVariant getVariant() const = 0;

    virtual bool isValidMove(IGameData& data, const Move& move) const = 0;
    virtual std::unordered_set<Move> getValidMoves(IGameData& data) const = 0;
    virtual std::unordered_set<Move> getValidMoves(IGameData& data, const Position& position) const = 0;

    virtual bool isUnderAttack(IGameData& data, const Position& position) const = 0;
    virtual bool isUnderAttack(IGameData& data, const Position& position, Color side) const = 0;
    virtual bool isCheck(IGameData& data) const = 0;
    virtual bool isCheck(IGameData& data, Color side) const = 0;

    virtual GameStatus getStatus(IGameData& data) const = 0;

    virtual IGameData& makeMove(IGameData& data, const Move& move) const = 0;
    virtual IGameData& undoMove(IGameData& data, std::size_t number=1) const = 0;

    virtual std::unique_ptr<IGameLogic> clone() const = 0;
};

#endif