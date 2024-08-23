#include "GameResult.h"

GameResult::GameResult() : status{GameResult::Status::ONGOING}, statusType{std::monostate{}}{}
GameResult::GameResult(VictoryType type) : status{GameResult::Status::VICTORY}, statusType{type}{}
GameResult::GameResult(DrawType type) : status{GameResult::Status::DRAW}, statusType{type}{}
GameResult::~GameResult(){}

GameResult::Status GameResult::getStatus() const{
    return status;
}

GameResult& GameResult::operator=(const GameResult& other){
    if (this == &other){
        return *this;
    }

    status = other.status;
    statusType = other.statusType;
    return *this;
}

bool GameResult::operator==(const GameResult& other) const{
    return (this->statusType == other.statusType);
}

bool GameResult::operator!=(const GameResult& other) const{
    return !(*this == other);
}

std::variant<GameResult::VictoryType, GameResult::DrawType, std::monostate> GameResult::getStatusType() const{
    return statusType;
}

GameResult& GameResult::setOngoing(){
    statusType = std::monostate{};
    status = GameResult::Status::ONGOING;
    return *this;
}
    
GameResult& GameResult::setStatusType(GameResult::VictoryType type){
    statusType = type;
    status = GameResult::Status::VICTORY;
    return *this;
}
    
GameResult& GameResult::setStatusType(GameResult::DrawType type){
    statusType = type;
    status = GameResult::Status::DRAW;
    return *this;
}