#ifndef PIECE_H
#define PIECE_H

#include <functional> // For std::hash
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

namespace std {
    template<>
    struct hash<Piece> {
        std::size_t operator()(const Piece& piece) const {
            std::size_t hashType{std::hash<PieceType>()(piece.getType())};
            std::size_t hashColor{std::hash<Color>()(piece.getColor())};

            return hashType ^ (hashColor << 1);
        }
    };
}

#endif