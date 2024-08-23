#ifndef ICHESSBOARD_H
#define ICHESSBOARD_H

#include <optional>
#include <string>
#include <utility> // For std::pair
#include "Piece.h"

// All of it's methods accepts file and rank in chess notation.
class IChessBoard{
public:
    virtual ~IChessBoard() = default;

    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual std::pair<int, int> getSize() const = 0;

    virtual bool isExist(int file, int rank) const = 0;
    virtual bool isEmpty(int file, int rank) const = 0;
    virtual std::optional<Piece> getAt(int file, int rank) const = 0;

    virtual IChessBoard& setAt(int file, int rank, const Piece& piece) = 0;
    virtual IChessBoard& clearAt(int file, int rank) = 0;
    virtual IChessBoard& removeAt(int file, int rank) = 0;
    virtual IChessBoard& clear() = 0;

    virtual std::string toFEN() const = 0;
    virtual IChessBoard& fromFEN(const std::string& FEN) = 0;
};

#endif