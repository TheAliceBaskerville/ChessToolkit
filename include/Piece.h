#ifndef PIECE_H
#define PIECE_H

#include <functional> // For std::hash
#include <stdexcept>
#include <string>
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
    Color color;
    PieceType type;
public:
    Piece(Color color, PieceType type);
    Piece(const Piece&) = default;
    Piece(Piece&&) noexcept = default;
    ~Piece() = default;

    Piece& operator=(const Piece&) = default;
    Piece& operator=(Piece&&) noexcept = default;
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

namespace EnumConverter{
    inline std::string toString(PieceType pieceType){
        switch (pieceType) {
            case PieceType::PAWN:   return "PAWN";
            case PieceType::KNIGHT: return "KNIGHT";
            case PieceType::BISHOP: return "BISHOP";
            case PieceType::ROOK:   return "ROOK";
            case PieceType::QUEEN:  return "QUEEN";
            case PieceType::KING:   return "KING";
            case PieceType::COUNT:  return "COUNT";
            default: throw std::out_of_range{"Unexpected PieceType given."};
        }
    }
}

#endif