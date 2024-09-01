#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <memory>
#include "Move.h"
#include "Color.h"
#include "GameStatus.h"
#include "ChessVariant.h"
#include "IChessBoard.h"

class ChessGameImpl;

class ChessGame{
private:
    ChessVariant variant;
    std::unique_ptr<ChessGameImpl> pImpl;
public:
    ChessGame(ChessVariant variant);
    ChessGame(const ChessGame& other);
    ChessGame(ChessGame&& other) noexcept;
    ~ChessGame();

    ChessGame& operator=(const ChessGame& other);
    ChessGame& operator=(ChessGame&& other) noexcept;

    ChessVariant getVariant() const;
    const IChessBoard& getBoard() const;
    const std::vector<Move>& getHistory() const;
    Color getCurrentTurn() const;

    bool isValidMove(const Move& move) const;
    std::unordered_set<Move> getValidMoves() const;
    std::unordered_set<Move> getValidMoves(const Position& position) const;

    bool isCheck() const;
    bool isCheck(Color color) const;

    GameStatus getStatus() const;
    ChessGame& makeMove(const Move& move);
    ChessGame& undoMove(std::size_t number=1);

    friend class MoveFactory;
};

#endif