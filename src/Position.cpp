#include "Position.h"

Position::Position(int file, int rank) : file{file}, rank{rank}{}

Position::Position(const std::pair<int, int>& pair) : file{pair.first}, rank{pair.second}{}

Position::Position(int boardHeight, int row, int column) : file{column + 1}, rank{boardHeight - row}{}

Position::Position(int boardHeight, const std::pair<int, int>& indexes) 
    : file{indexes.second + 1}, rank{boardHeight - indexes.first}{}

Position::Position(const Position& other) : file{other.file}, rank{other.rank}{}

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
    return std::make_pair(file, rank);
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

std::pair<int, int> Position::toIndex(int boardHeight) const{
    return std::make_pair(boardHeight - rank, file - 1);
}

Position Position::offset(int fileOffset, int rankOffset) const{
    return Position{file + fileOffset, rank + rankOffset};
}

Position Position::offset(const std::pair<int, int>& offset) const{
    return this->offset(offset.first, offset.second);
}