#ifndef CHESSGAMEIMPL_H
#define CHESSGAMEIMPL_H

#include <memory>
#include "IGameData.h"
#include "IGameLogic.h"
#include "GameStatus.h"
#include "MoveFactory.h"

class ChessGameImpl {
private:
    std::unique_ptr<IGameData> data;
    std::unique_ptr<IGameLogic> logic;
public:
    explicit ChessGameImpl(ChessVariant variant);
    ChessGameImpl(const ChessGameImpl& other);
    ChessGameImpl(ChessGameImpl&& other) noexcept;
    ~ChessGameImpl();

    ChessGameImpl& operator=(const ChessGameImpl& other);
    ChessGameImpl& operator=(ChessGameImpl&& other) noexcept;

    const IChessBoard& getBoard() const;
    const std::vector<Move>& getHistory() const;
    Color getCurrentTurn() const;

    bool isValidMove(const Move& move) const;
    std::unordered_set<Move> getValidMoves() const;
    std::unordered_set<Move> getValidMoves(const Position& position) const;

    bool isCheck() const;
    bool isCheck(Color color) const;

    GameStatus getStatus() const;
    ChessGameImpl& makeMove(const Move& move);
    ChessGameImpl& undoMove(std::size_t number);

    friend class MoveFactory;
};

#endif