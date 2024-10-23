#ifndef CLASSICCONSTANTS_H
#define CLASSICCONSTANTS_H

#include <unordered_set>
#include "Piece.h"

const std::unordered_set<PieceType> CLASSIC_PROMOTION_POSSIBLE_CHOICES = {
    PieceType::BISHOP, PieceType::KNIGHT, PieceType::ROOK, PieceType::QUEEN
};

#endif