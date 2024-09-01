#ifndef ICHESSBOARD_H
#define ICHESSBOARD_H

#include <optional>
#include <string>
#include "Position.h"
#include "Piece.h"
#include "FEN.h"

class IChessBoard{ // TODO: think on adding iterators for it.
public:
    virtual ~IChessBoard() = default;

    virtual std::size_t getWidth() const = 0;
    virtual std::size_t getHeight() const = 0;
    virtual std::pair<std::size_t, std::size_t> getSize() const = 0;

    virtual bool isExist(const Position& position) const = 0;
    virtual bool isEmpty(const Position& position) const = 0;
    virtual std::optional<Piece> getAt(const Position& position) const = 0;

    virtual IChessBoard& setAt(const Position& position, const Piece& piece) = 0;
    virtual IChessBoard& clearAt(const Position& position) = 0;
    virtual IChessBoard& removeAt(const Position& position) = 0;
    virtual IChessBoard& clear() = 0;

    virtual IChessBoard& fromFEN(const FEN& FEN) = 0;

    virtual std::unique_ptr<IChessBoard> clone() const = 0;
};

#endif