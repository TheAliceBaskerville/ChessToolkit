#ifndef CLASSICHESSGAME_H
#define CLASSICHESSGAME_H

#include <memory>
#include "FEN.h"
#include "Board.h"
#include "GameStatus.h"
#include "variants/Classic/data/ClassicMove.h"
#include "variants/Classic/data/ClassicMoveConstruct.h"

class ClassicChessGame{
private:
    class ClassicChessGameImpl;
    std::unique_ptr<ClassicChessGameImpl> pImpl;
public:
    ClassicChessGame();
    ClassicChessGame(const FEN& fen);
    ClassicChessGame(const ClassicChessGame& other);
    ClassicChessGame(ClassicChessGame&&) = default;
    ~ClassicChessGame();

    ClassicChessGame& operator=(const ClassicChessGame& other);
    ClassicChessGame& operator=(ClassicChessGame&&) = default;

    const Board& getBoard() const;
    std::vector<ClassicMove> getHistory() const;
    Color getCurrentTurn() const;

    std::unordered_set<ClassicMoveConstruct> getValidMoves(const Position& position) const;
    bool isCheck() const;
    GameStatus getStatus() const;

    ClassicChessGame& makeMove(const ClassicMoveConstruct& moveData);
    ClassicChessGame& undoMove(std::size_t number);
};

#endif