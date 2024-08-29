#ifndef POSITION_H
#define POSITION_H

#include <utility> // For std::pair

class Position{
private:
    int file, rank;
public:
    Position(int file=0, int rank=0);
    Position(const std::pair<int, int>& pair);
    ~Position();

    Position& operator=(const Position& other);
    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;

    int getFile() const;
    int getRank() const;
    std::pair<int, int> getPair() const;

    Position& setFile(int file);
    Position& setRank(int rank);
    Position& setPair(const std::pair<int, int>& pair);

    std::pair<int, int> toIndex(int boardSize) const;
};

#endif