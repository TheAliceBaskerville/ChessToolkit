#include <stdexcept>
#include "GameStatus.h"

Status GameStatus::getFromDetailed(DetailedStatus status) const{
    switch (status) {
        case DetailedStatus::ONGOING:
            return Status::ONGOING;
        case DetailedStatus::CHECKMATE:
            return Status::VICTORY;
        case DetailedStatus::STALEMATE:
        case DetailedStatus::THREEFOLD_REPETITION:
        case DetailedStatus::INSUFFICIENT_MATERIAL:
        case DetailedStatus::FIFTY_MOVES_RULE:
            return Status::DRAW;
        default:
            throw std::invalid_argument{"Unexpected DetailedStatus given."};
    }
}

GameStatus::GameStatus(DetailedStatus status) : status{status}{}

GameStatus::~GameStatus(){}

GameStatus& GameStatus::operator=(const GameStatus& other){
    status = other.status;
    return *this;
}

bool GameStatus::operator==(const GameStatus& other) const{
    return (status == other.status);
}

bool GameStatus::operator!=(const GameStatus& other) const{
    return !(*this==other);
}

Status GameStatus::getStatus() const{
    return getFromDetailed(status);
}

DetailedStatus GameStatus::getDetailedType() const{
    return status;
}

GameStatus& GameStatus::setStatus(DetailedStatus newStatus){
    status = newStatus;
    return *this;
}