#ifndef ISQUARE_H
#define ISQUARE_H

#include <optional>
#include "Piece.h"

class ISquare{
public:
    virtual ~ISquare() = default;

    virtual bool operator==(const ISquare& other) const = 0;
    bool operator!=(const ISquare& other) const {return !(*this == other);}

    virtual bool isExist() const = 0;
    virtual bool isEmpty() const = 0;
    virtual std::optional<Piece> getPiece() const = 0;
    virtual ISquare& setPiece(const Piece& piece) = 0;
    virtual ISquare& setEmpty() = 0;

    virtual std::unique_ptr<ISquare> clone() const = 0;
};

#endif