#include <stdexcept>
#include <sstream>
#include "variants/Classic/ClassicChessGameImpl.h"

ClassicChessGame::ClassicChessGame() : pImpl{std::make_unique<ClassicChessGameImpl>()}{}

ClassicChessGame::ClassicChessGame(const FEN& fen) : pImpl{std::make_unique<ClassicChessGameImpl>(fen)}{}

ClassicChessGame::ClassicChessGame(const ClassicChessGame& other) 
    : pImpl{std::make_unique<ClassicChessGameImpl>(*other.pImpl)}{}

ClassicChessGame::~ClassicChessGame() = default;

ClassicChessGame& ClassicChessGame::operator=(const ClassicChessGame& other){
    if (this == &other) {
        return *this;
    }

    pImpl = std::make_unique<ClassicChessGameImpl>(*other.pImpl);
    return *this;
}

const Board& ClassicChessGame::getBoard() const{
    return pImpl->getBoard();
}

std::vector<ClassicMove> ClassicChessGame::getHistory() const{
    return pImpl->getHistory();
}

Color ClassicChessGame::getCurrentTurn() const{
    return pImpl->getCurrentTurn();
}

std::unordered_set<ClassicMoveConstruct> ClassicChessGame::getValidMoves(const Position& position) const{
    return pImpl->getValidMoves(position);
}

bool ClassicChessGame::isCheck() const{
    return pImpl->isCheck();
}

GameStatus ClassicChessGame::getStatus() const{
    return pImpl->getStatus();
}

ClassicChessGame& ClassicChessGame::makeMove(const ClassicMoveConstruct& moveData){
    pImpl->makeMove(moveData);
    return *this;
}

ClassicChessGame& ClassicChessGame::undoMove(std::size_t number){
    pImpl->undoMove(number);
    return *this;
}