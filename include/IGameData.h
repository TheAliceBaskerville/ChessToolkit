#ifndef IGAMEDATA_H
#define IGAMEDATA_H

#include <memory>
#include "Move.h"
#include "IChessBoard.h"
#include "ChessVariant.h"

class IGameData{
public:
    virtual ~IGameData() = default;

    virtual ChessVariant getVariant() const = 0;

    virtual IChessBoard& accessBoard() = 0;
    virtual const IChessBoard& getBoard() const = 0;
    virtual IGameData& setBoard(std::unique_ptr<IChessBoard> board) = 0;

    virtual const std::vector<Move>& getHistory() const = 0;
    virtual IGameData& appendHistory(const Move& move) = 0;
    virtual IGameData& removeHistory(std::size_t number=1) = 0;
    virtual IGameData& clearHistory() = 0;
    virtual Move popHistory() = 0;

    virtual Color getCurrentTurn() const = 0;
    virtual IGameData& setCurrentTurn(Color currentTurn) = 0;

    virtual std::unique_ptr<IGameData> clone() const = 0;
};

#endif