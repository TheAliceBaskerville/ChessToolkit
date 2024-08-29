#include "Move.h"

Move::Move(int startFile, int startRank, int endFile, int endRank,
     bool isEnPassant, bool isPawnPromotion, const std::optional<Piece>& promotionChoice, 
     const std::optional<Piece>& movedPiece, const std::optional<Piece>& capturedPiece)
    : startFile{startFile}, startRank{startRank}, endFile{endFile}, endRank{endRank},
      isEnPassantFlag{isEnPassant}, isPawnPromotionFlag{isPawnPromotion}, promotionChoice{promotionChoice},
      movedPiece{movedPiece}, capturedPiece{capturedPiece}{}

Move::~Move(){}

Move& Move::operator=(const Move& other){
    if (this == &other){
        return *this;
    }

    startFile = other.startFile;
    startRank = other.startRank;
    endFile = other.endFile;
    endRank = other.endRank;
    isEnPassantFlag = other.isEnPassantFlag;
    isPawnPromotionFlag = other.isPawnPromotionFlag;
    movedPiece = other.movedPiece;
    capturedPiece = other.capturedPiece;

    return *this;
}

bool Move::operator==(const Move& other) const{
    return (startFile == other.startFile &&
           startRank == other.startRank &&
           endFile == other.endFile &&
           endRank == other.endRank &&
           isEnPassantFlag == other.isEnPassantFlag &&
           isPawnPromotionFlag == other.isPawnPromotionFlag &&
           movedPiece == other.movedPiece &&
           capturedPiece == other.capturedPiece);
}

bool Move::operator!=(const Move& other) const{
    return !(*this == other);
}

int Move::getStartFile() const{
    return startFile;
}

int Move::getStartRank() const{
    return startRank;
}

int Move::getEndFile() const{
    return endFile;
}

int Move::getEndRank() const{
    return endRank;
}

std::pair<int, int> Move::getStart() const{
    return {startFile, startRank};
}

std::pair<int, int> Move::getEnd() const{
    return {endFile, endRank};
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