#ifndef POSITION_H
#define POSITION_H

#include <functional> // For std::hash
#include <utility> // For std::pair

class Position{
private:
    std::size_t file, rank;
public:
    Position(std::size_t file=0, std::size_t rank=0);
    Position(const std::pair<std::size_t, std::size_t>& pair);
    Position(std::size_t boardHeight, std::size_t row, std::size_t column);
    Position(std::size_t boardHeight, const std::pair<std::size_t, std::size_t>& indexes);
    Position(const Position&) = default;
    Position(Position&&) noexcept = default;
    ~Position() = default;

    Position& operator=(const Position&) = default;
    Position& operator=(Position&&) noexcept = default;
    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;

    std::size_t getFile() const;
    std::size_t getRank() const;
    std::pair<std::size_t, std::size_t> getPair() const;

    Position& setFile(std::size_t file);
    Position& setRank(std::size_t rank);
    Position& setPair(const std::pair<std::size_t, std::size_t>& pair);

    std::pair<std::size_t, std::size_t> toIndex(std::size_t boardHeight) const;
    Position offset(int fileOffset, int rankOffset) const;
    Position offset(const std::pair<int, int>& offset) const;
};

namespace std{
    template<>
    struct hash<Position>{
        std::size_t operator()(const Position& position) const{
            std::size_t hashFile{std::hash<std::size_t>()(position.getFile())};
            std::size_t hashRank{std::hash<std::size_t>()(position.getRank())};

            return hashFile ^ (hashRank << 1);
        }
    };
}

#endif