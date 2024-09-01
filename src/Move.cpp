#include "Move.h"

Move::Move(const Position& start, const Position& end, bool isEnPassant, bool isPawnPromotion, bool isCastling,
           const std::optional<Piece>& promotionChoice, const std::optional<Piece>& movedPiece,
           const std::optional<Piece>& capturedPiece, const std::unordered_set<std::size_t>& castlingRemovals)
           : start{start}, end{end}, isEnPassantFlag{isEnPassant}, isPawnPromotionFlag{isPawnPromotion},
           isCastlingFlag{isCastling}, promotionChoice{promotionChoice}, movedPiece{movedPiece},
           capturedPiece{capturedPiece}, castlingRemovals{castlingRemovals}{}

Move::Move(const Move& other)
    : start{other.start}, end{other.end}, isEnPassantFlag{other.isEnPassantFlag},
      isPawnPromotionFlag{other.isPawnPromotionFlag}, isCastlingFlag{other.isCastlingFlag},
      promotionChoice{other.promotionChoice}, movedPiece{other.movedPiece},
      capturedPiece{other.capturedPiece}, castlingRemovals{other.castlingRemovals}{}

Move::Move(Move&& other)
    : start{std::move(other.start)}, end{std::move(other.end)},isEnPassantFlag{std::move(other.isEnPassantFlag)},
      isPawnPromotionFlag{std::move(other.isPawnPromotionFlag)}, isCastlingFlag{std::move(other.isCastlingFlag)},
      promotionChoice{std::move(other.promotionChoice)}, movedPiece{std::move(other.movedPiece)},
      capturedPiece{std::move(other.capturedPiece)}, castlingRemovals{std::move(other.castlingRemovals)}{}

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

Move& Move::operator=(Move&& other){
    if (this == &other){
        return *this;
    }
    
    start = std::move(other.start);
    end = std::move(other.end);
    isEnPassantFlag = std::move(other.isEnPassantFlag);
    isPawnPromotionFlag = std::move(other.isPawnPromotionFlag);
    isCastlingFlag = std::move(other.isCastlingFlag);
    promotionChoice = std::move(other.promotionChoice);
    movedPiece = std::move(other.movedPiece);
    capturedPiece = std::move(other.capturedPiece);
    castlingRemovals = std::move(other.castlingRemovals);

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

std::unordered_set<std::size_t> Move::getCastlingRemovals() const{
    return castlingRemovals;
}

bool Move::isCastling() const{
    return isCastlingFlag;
}