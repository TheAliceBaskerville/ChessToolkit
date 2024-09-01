#include <stdexcept>
#include <sstream>
#include "ChessGameImpl.h"
#include "ClassicGameData.h"
#include "ClassicGameLogic.h"

ChessGameImpl::ChessGameImpl(ChessVariant variant){
    switch (variant) {
        case ChessVariant::CLASSIC:
            data = std::make_unique<ClassicGameData>();
            logic = std::make_unique<ClassicGameLogic>();
            break;
        default:
            throw std::invalid_argument("Unsupported chess variant" + EnumConverter::toString(variant));
    }
}

ChessGameImpl::ChessGameImpl(const ChessGameImpl& other){
    if (other.data){
        data = other.data->clone();
    }
    else{
        data = nullptr;
    }
    if (other.logic){
        logic = other.logic->clone();
    }
    else{
        logic = nullptr;
    }
}

ChessGameImpl::ChessGameImpl(ChessGameImpl&& other) noexcept
    : data{std::move(other.data)}, logic{std::move(other.logic)}{}

ChessGameImpl::~ChessGameImpl(){}

ChessGameImpl& ChessGameImpl::operator=(const ChessGameImpl& other){
    if (this == &other) {
        return *this;
    }

    if (other.data){
        data = other.data->clone();
    }
    else{
        data = nullptr;
    }
    if (other.logic){
        logic = other.logic->clone();
    }
    else{
        logic = nullptr;
    }

    return *this;
}

ChessGameImpl& ChessGameImpl::operator=(ChessGameImpl&& other) noexcept{
    data = std::move(other.data);
    logic = std::move(other.logic);
    return *this;
}

const IChessBoard& ChessGameImpl::getBoard() const{
    return data->getBoard();
}

const std::vector<Move>& ChessGameImpl::getHistory() const{
    return data->getHistory();
}

Color ChessGameImpl::getCurrentTurn() const{
    return data->getCurrentTurn();
}

bool ChessGameImpl::isValidMove(const Move& move) const{
    return logic->isValidMove(*data, move);
}

std::unordered_set<Move> ChessGameImpl::getValidMoves() const{
    return logic->getValidMoves(*data);
}

std::unordered_set<Move> ChessGameImpl::getValidMoves(const Position& position) const{
    return logic->getValidMoves(*data, position);
}

bool ChessGameImpl::isCheck() const{
    return logic->isCheck(*data);
}

bool ChessGameImpl::isCheck(Color color) const{
    return logic->isCheck(*data, color);
}

GameStatus ChessGameImpl::getStatus() const{
    return logic->getStatus(*data);
}

ChessGameImpl& ChessGameImpl::makeMove(const Move& move){
    if (!logic->isValidMove(*data, move)){
        std::stringstream errorMessage;
        errorMessage << "Invalid move given: start = (" << move.getStart().getFile() << ", " <<
                        move.getStart().getRank() << "), end = (" << move.getEnd().getFile() << ", " <<
                        move.getEnd().getRank() << ").";
        throw std::invalid_argument{errorMessage.str()};
    }
    logic->makeMove(*data, move);
    return *this;
}

ChessGameImpl& ChessGameImpl::undoMove(std::size_t number){
    logic->undoMove(*data, number);
    return *this;
}