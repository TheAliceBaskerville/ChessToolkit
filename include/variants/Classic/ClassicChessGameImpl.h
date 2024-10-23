#ifndef CLASSICCHESSGAMEIMPL_H
#define CLASSICCHESSGAMEIMPL_H

#include "variants/Classic/ClassicChessGame.h"
#include "variants/Classic/data/ClassicGameData.h"

class ClassicChessGame::ClassicChessGameImpl{
private:
    ClassicGameData data;
public:
    ClassicChessGameImpl();
    ClassicChessGameImpl(const FEN& fen);
    ClassicChessGameImpl(const ClassicChessGameImpl&) = default;
    ClassicChessGameImpl(ClassicChessGameImpl&&) = default;
    ~ClassicChessGameImpl() = default;

    ClassicChessGameImpl& operator=(const ClassicChessGameImpl&) = default;
    ClassicChessGameImpl& operator=(ClassicChessGameImpl&&) = default;

    const Board& getBoard() const;
    std::vector<ClassicMove> getHistory() const;
    Color getCurrentTurn() const;
    std::unordered_set<ClassicMoveConstruct> getValidMoves(const Position& position) const;
    bool isCheck() const;
    GameStatus getStatus() const;

    ClassicChessGameImpl& makeMove(const ClassicMoveConstruct& moveData);
    ClassicChessGameImpl& undoMove(std::size_t number);
};

#endif