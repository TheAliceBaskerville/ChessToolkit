#include "GameResult.h"
#include <stdexcept>

Status GameStatus::getFromDetailed(DetailedStatus detailedStatus){
    switch (detailedStatus) {
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

GameStatus::GameStatus(DetailedStatus detailedStatus) 
    : detailedStatus{detailedStatus}, status{getFromDetailed(detailedStatus)}{}

GameStatus::~GameStatus(){}

GameStatus& GameStatus::operator=(const GameStatus& other){
    detailedStatus = other.detailedStatus;
    status = other.status;
    return *this;
}

bool GameStatus::operator==(const GameStatus& other) const{
    return (detailedStatus == other.detailedStatus);
}

bool GameStatus::operator!=(const GameStatus& other) const{
    return !(*this==other);
}

Status GameStatus::getStatus() const{
    return status;
}

DetailedStatus GameStatus::getDetailedType() const{
    return detailedStatus;
}

GameStatus& GameStatus::setStatus(DetailedStatus newStatus){
    detailedStatus = newStatus;
    status = getFromDetailed(newStatus);
    return *this;
}