#ifndef PIECE_H
#define PIECE_H

#include "Color.h"

enum class PieceType{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    COUNT
};

class Piece{
private:
    PieceType type;
    Color color;
public:
    Piece(Color color, PieceType type);
    ~Piece();

    Piece& operator=(const Piece& other);
    bool operator==(const Piece& other) const;
    bool operator!=(const Piece& other) const;

    PieceType getType() const;
    Color getColor() const;

    Piece& setType(PieceType type);
    Piece& setColor(Color color);
};

#endif