#include "Move.h"

Move::Move(const Position& start, const Position& end, bool isEnPassant, bool isPawnPromotion, bool isCastling,
           const std::optional<Piece>& promotionChoice, const std::optional<Piece>& movedPiece,
           const std::optional<Piece>& capturedPiece, const std::unordered_set<int>& castlingRemovals)
           : start{start}, end{end}, isEnPassantFlag{isEnPassant}, isPawnPromotionFlag{isPawnPromotion},
           isCastlingFlag{isCastling}, promotionChoice{promotionChoice}, movedPiece{movedPiece},
           capturedPiece{capturedPiece}, castlingRemovals{castlingRemovals}{}

Move::~Move(){}

Move& Move::operator=(const Move& other){
    if (this == &other){
        return *this;
    }

    start = other.start;
    end = other.end;
    isEnPassantFlag = other.isEnPassantFlag;
    isPawnPromotionFlag = other.isPawnPromotionFlag;
    isCastlingFlag = other.isCastlingFlag;
    movedPiece = other.movedPiece;
    capturedPiece = other.capturedPiece;
    castlingRemovals = other.castlingRemovals;

    return *this;
}

bool Move::operator==(const Move& other) const{
    return (start == other.start &&
           end == other.end &&
           isEnPassantFlag == other.isEnPassantFlag &&
           isPawnPromotionFlag == other.isPawnPromotionFlag &&
           isCastlingFlag == other.isCastlingFlag &&
           movedPiece == other.movedPiece &&
           capturedPiece == other.capturedPiece &&
           castlingRemovals == other.castlingRemovals);
}

bool Move::operator!=(const Move& other) const{
    return !(*this == other);
}

Position Move::getStart() const{
    return start;
}

Position Move::getEnd() const{
    return end;
}

bool Move::isEnPassant() const{
    return isEnPassantFlag;
}

bool Move::isPawnPromotion() const{
    return isPawnPromotionFlag;
}

std::optional<Piece> Move::getPromotionChoice() const{
    return promotionChoice;
}

std::optional<Piece> Move::getMovedPiece() const{
    return movedPiece;
}

std::optional<Piece> Move::getCapturedPiece() const{
    return capturedPiece;
}

bool Move::isCapture() const{
    return capturedPiece.has_value();
}

bool Move::hasMovedPiece() const{
    return movedPiece.has_value();
}

std::unordered_set<int> Move::getCastlingRemovals() const{
    return castlingRemovals;
}

bool Move::isCastling() const{
    return isCastlingFlag;
}