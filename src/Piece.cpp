#include "Piece.h"

Piece::Piece(Color color, PieceType type) : color{color}, type{type}{}

bool Piece::operator==(const Piece& other) const{
    return (color == other.color && type == other.type);
}

bool Piece::operator!=(const Piece& other) const{
    return !(*this == other);
}

PieceType Piece::getType() const{
    return type;
}

Color Piece::getColor() const{
    return color;
}

Piece& Piece::setType(PieceType type){
    this->type = type;
    return *this;
}

Piece& Piece::setColor(Color color){
    this->color = color;
    return *this;
}