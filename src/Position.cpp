#include <stdexcept>
#include <sstream>
#include "Position.h"

Position::Position(std::size_t file, std::size_t rank) : file{file}, rank{rank}{}

Position::Position(const std::pair<std::size_t, std::size_t>& pair) : file{pair.first}, rank{pair.second}{}

Position::Position(std::size_t boardHeight, std::size_t row, std::size_t column) : file{column + 1}{
    if (boardHeight - row < 1){
        std::stringstream errorMessage;
        errorMessage << "Index out of range: (" << row << ", " << column << "), given boardHeight = " << boardHeight;
        throw std::out_of_range{errorMessage.str()};
    }
    rank = boardHeight - row;
}

Position::Position(std::size_t boardHeight, const std::pair<std::size_t, std::size_t>& indexes) 
    : file{indexes.second + 1}{
    if (boardHeight - indexes.first < 1){
        std::stringstream errorMessage;
        errorMessage << "Index out of range: (" << indexes.first << ", " << indexes.first <<
                        "), given boardHeight = " << boardHeight;
        throw std::out_of_range{errorMessage.str()};
    }
    rank = boardHeight - indexes.first;
}


bool Position::operator==(const Position& other) const{
    return (file == other.file && rank == other.rank);
}

bool Position::operator!=(const Position& other) const{
    return !(*this==other);
}

std::size_t Position::getFile() const{
    return file;
}

std::size_t Position::getRank() const{
    return rank;
}

std::pair<std::size_t, std::size_t> Position::getPair() const{
    return std::make_pair(file, rank);
}

Position& Position::setFile(std::size_t file){
    this->file = file;
    return *this;
}

Position& Position::setRank(std::size_t rank){
    this->rank = rank;
    return *this;
}

Position& Position::setPair(const std::pair<std::size_t, std::size_t>& pair){
    file = pair.first;
    rank = pair.second;
    return *this;
}

std::pair<std::size_t, std::size_t> Position::toIndex(std::size_t boardHeight) const{
    return std::make_pair(boardHeight - rank, file - 1);
}

Position Position::offset(int fileOffset, int rankOffset) const{
    int newFile{static_cast<int>(file) + fileOffset}, newRank{static_cast<int>(rank) + rankOffset};
    if (newFile < 0) {
        std::stringstream errorMessage;
        errorMessage << "File offset results in a negative rank index: " << newFile;
        throw std::out_of_range{errorMessage.str()};
    }
    if (newRank < 0) {
        std::stringstream errorMessage;
        errorMessage << "Rank offset results in a negative rank index: " << newRank;
        throw std::out_of_range{errorMessage.str()};
    }
    return Position{static_cast<std::size_t>(newFile), static_cast<std::size_t>(newRank)};
}

Position Position::offset(const std::pair<int, int>& offset) const{
    return this->offset(offset.first, offset.second);
}