#ifndef ICHESSBOARD_H
#define ICHESSBOARD_H

#include <optional>
#include <string>
#include "Position.h"
#include "Piece.h"
#include "FEN.h"

// All of it's methods accepts file and rank in chess notation.
class IChessBoard{ // TODO: think on adding iterators for it.
public:
    virtual ~IChessBoard() = default;

    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual std::pair<int, int> getSize() const = 0;

    virtual bool isExist(const Position& position) const = 0;
    virtual bool isEmpty(const Position& position) const = 0;
    virtual std::optional<Piece> getAt(const Position& position) const = 0;

    virtual IChessBoard& setAt(const Position& position, const Piece& piece) = 0;
    virtual IChessBoard& clearAt(const Position& position) = 0;
    virtual IChessBoard& removeAt(const Position& position) = 0;
    virtual IChessBoard& clear() = 0;

    virtual IChessBoard& fromFEN(const FEN& FEN) = 0;
};

#endif