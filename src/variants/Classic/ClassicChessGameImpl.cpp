#include <stdexcept>
#include <sstream>
#include "variants/Classic/ClassicChessGameImpl.h"
#include "variants/Classic/logic/ClassicGameLogic.h"

ClassicChessGame::ClassicChessGameImpl::ClassicChessGameImpl() : data{}{}

ClassicChessGame::ClassicChessGameImpl::ClassicChessGameImpl(const FEN& fen) : data{fen}{}

const Board& ClassicChessGame::ClassicChessGameImpl::getBoard() const{
    return data.getBoard();
}

std::vector<ClassicMove> ClassicChessGame::ClassicChessGameImpl::getHistory() const{
    std::vector<ClassicMove> result;
    result.reserve(data.getHistory().size());
    for (const ClassicMoveRecord& moveRecord : data.getHistory()){
        result.push_back(moveRecord.getMove());
    }
    return result;
}

Color ClassicChessGame::ClassicChessGameImpl::getCurrentTurn() const{
    return data.getCurrentTurn();
}

std::unordered_set<ClassicMoveConstruct> ClassicChessGame::ClassicChessGameImpl::getValidMoves(const Position& position) const{
    return ClassicGameLogic::getValidMoves(data, position);
}

bool ClassicChessGame::ClassicChessGameImpl::isCheck() const{
    return ClassicGameLogic::isCheck(data);
}

GameStatus ClassicChessGame::ClassicChessGameImpl::getStatus() const{
    return ClassicGameLogic::getStatus(data);
}

ClassicChessGame::ClassicChessGameImpl& ClassicChessGame::ClassicChessGameImpl::makeMove(const ClassicMoveConstruct& moveData){
    ClassicGameLogic::appendMove(data, moveData);
    return *this;
}

ClassicChessGame::ClassicChessGameImpl& ClassicChessGame::ClassicChessGameImpl::undoMove(std::size_t number){
    ClassicGameLogic::undoMove(data, number);
    return *this;
}