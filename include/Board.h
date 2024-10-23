#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>
#include "FEN.h"
#include "ISquare.h"

class Board{
private:
    std::size_t width, height;
    std::vector<std::vector<std::unique_ptr<ISquare>>> board;
    const Position& boundaryCheck(const Position& position) const;
public:
    Board(std::size_t height=8, std::size_t width=8);
    Board(const Board& other);
    Board(Board&&) noexcept = default;
    ~Board() = default;

    Board& operator=(const Board& other);
    Board& operator=(Board&&) noexcept = default;

    bool operator==(const Board& other) const;
    bool operator!=(const Board& other) const;

    std::size_t getWidth() const;
    std::size_t getHeight() const;
    std::pair<std::size_t, std::size_t> getSize() const;

    bool isExist(const Position& position) const;
    bool isEmpty(const Position& position) const;
    std::optional<Piece> getAt(const Position& position) const;

    Board& setAt(const Position& position, const Piece& piece);
    Board& clearAt(const Position& position);
    Board& removeAt(const Position& position);
    Board& restoreAt(const Position& position);
    Board& clear();
};

#endif