#ifndef ICHESSBOARD_H
#define ICHESSBOARD_H

#include <optional>
#include <string>
#include <utility> // For std::pair
#include "Piece.h"
#include "FEN.h"

// All of it's methods accepts file and rank in chess notation.
class IChessBoard{
public:
    virtual ~IChessBoard() = default;

    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual std::pair<int, int> getSize() const = 0;

    virtual bool isExist(int file, int rank) const = 0;
    virtual bool isExist(std::pair<int, int> position) const = 0;
    virtual bool isEmpty(int file, int rank) const = 0;
    virtual bool isEmpty(std::pair<int, int> position) const = 0;
    virtual std::optional<Piece> getAt(int file, int rank) const = 0;
    virtual std::optional<Piece> getAt(std::pair<int, int> position) const = 0;

    virtual IChessBoard& setAt(int file, int rank, const Piece& piece) = 0;
    virtual IChessBoard& setAt(std::pair<int, int> position, const Piece& piece) = 0;
    virtual IChessBoard& clearAt(int file, int rank) = 0;
    virtual IChessBoard& clearAt(std::pair<int, int> position) = 0;
    virtual IChessBoard& removeAt(int file, int rank) = 0;
    virtual IChessBoard& removeAt(std::pair<int, int> position) = 0;
    virtual IChessBoard& clear() = 0;

    virtual IChessBoard& fromFEN(const FEN& FEN) = 0;
};

#endif