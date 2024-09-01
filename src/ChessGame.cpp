#include <stdexcept>
#include <sstream>
#include "ChessGame.h"
#include "ChessGameImpl.h"

ChessGame::ChessGame(ChessVariant variant) : variant{variant}, pImpl{std::make_unique<ChessGameImpl>(variant)}{}

ChessGame::ChessGame(const ChessGame& other) 
    : variant{other.variant}, pImpl{std::make_unique<ChessGameImpl>(*other.pImpl)}{}

ChessGame::ChessGame(ChessGame&& other) noexcept
    : variant{other.variant}, pImpl{std::move(other.pImpl)}{}

ChessGame::~ChessGame(){}

ChessGame& ChessGame::operator=(const ChessGame& other){
    if (this == &other) {
        return *this;
    }

    variant = other.variant;
    pImpl = std::make_unique<ChessGameImpl>(*other.pImpl);
    return *this;
}

ChessGame& ChessGame::operator=(ChessGame&& other) noexcept{
    if (this == &other) { 
        return *this;
    }
    
    variant = std::move(other.variant);
    pImpl = std::move(other.pImpl);
    return *this;
}

ChessVariant ChessGame::getVariant() const{
    return variant;
}

const IChessBoard& ChessGame::getBoard() const{
    return pImpl->getBoard();
}

const std::vector<Move>& ChessGame::getHistory() const{
    return pImpl->getHistory();
}

Color ChessGame::getCurrentTurn() const{
    return pImpl->getCurrentTurn();
}

bool ChessGame::isValidMove(const Move& move) const{
    return pImpl->isValidMove(move);
}

std::unordered_set<Move> ChessGame::getValidMoves() const{
    return pImpl->getValidMoves();
}

std::unordered_set<Move> ChessGame::getValidMoves(const Position& position) const{
    return pImpl->getValidMoves(position);
}

bool ChessGame::isCheck() const{
    return pImpl->isCheck();
}

bool ChessGame::isCheck(Color color) const{
    return pImpl->isCheck(color);
}

GameStatus ChessGame::getStatus() const{
    return pImpl->getStatus();
}

ChessGame& ChessGame::makeMove(const Move& move){
    pImpl->makeMove(move);
    return *this;
}

ChessGame& ChessGame::undoMove(std::size_t number){
    pImpl->undoMove(number);
    return *this;
}