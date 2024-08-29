#include "Position.h"

Position::Position(int file, int rank) : file{file}, rank{rank}{}

Position::Position(const std::pair<int, int>& pair) : file{pair.first}, rank{pair.second}{}

Position::~Position(){}

Position& Position::operator=(const Position& other){
    file = other.file;
    rank = other.rank;
    return *this;
}

bool Position::operator==(const Position& other) const{
    return (file == other.file && rank == other.rank);
}

bool Position::operator!=(const Position& other) const{
    return !(*this==other);
}

int Position::getFile() const{
    return file;
}

int Position::getRank() const{
    return rank;
}

std::pair<int, int> Position::getPair() const{
    return std::pair<int, int>{file, rank};
}

Position& Position::setFile(int file){
    this->file = file;
    return *this;
}

Position& Position::setRank(int rank){
    this->rank = rank;
    return *this;
}

Position& Position::setPair(const std::pair<int, int>& pair){
    file = pair.first;
    rank = pair.second;
    return *this;
}

std::pair<int, int> Position::toIndex(int boardSize) const{
    return std::pair{boardSize - rank, file - 1};
}