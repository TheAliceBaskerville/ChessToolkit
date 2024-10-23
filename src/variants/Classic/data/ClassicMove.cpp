#include "variants/Classic/data/ClassicMove.h"

ClassicMove::ClassicMove(const Position& start, const Position& end, const Piece& movedPiece, 
                         const std::optional<Piece>& capturedPiece, bool isEnPassant, bool isPawnPromotion,
                         bool isCastling, const std::optional<Piece>& promotionChoice,
                         const std::unordered_set<std::size_t>& castlingRemovals, bool isCheckFlag,
                         bool isCheckmateFlag, const std::string& notation)
    : start{start}, end{end}, movedPiece{movedPiece}, capturedPiece{capturedPiece}, isEnPassantFlag{isEnPassant},
      isPawnPromotionFlag{isPawnPromotion}, isCastlingFlag{isCastling}, promotionChoice{promotionChoice},
      castlingRemovals{castlingRemovals}, isCheckFlag{isCheckFlag}, isCheckmateFlag{isCheckmateFlag},
      notation{notation}{}

bool ClassicMove::operator==(const ClassicMove& other) const{
    return (start == other.start &&
            end == other.end &&
            movedPiece == other.movedPiece &&
            capturedPiece == other.capturedPiece &&
            isEnPassantFlag == other.isEnPassantFlag &&
            isPawnPromotionFlag == other.isPawnPromotionFlag &&
            isCastlingFlag == other.isCastlingFlag &&
            promotionChoice == other.promotionChoice &&
            castlingRemovals == other.castlingRemovals &&
            isCheckFlag == other.isCheckFlag &&
            isCheckmateFlag == other.isCheckmateFlag &&
            notation == other.notation);
}

bool ClassicMove::operator!=(const ClassicMove& other) const{
    return !(*this == other);
}

Position ClassicMove::getStart() const{
    return start;
}

Position ClassicMove::getEnd() const{
    return end;
}

Piece ClassicMove::getMovedPiece() const{
    return movedPiece;
}

std::optional<Piece> ClassicMove::getCapturedPiece() const{
    return capturedPiece;
}

bool ClassicMove::isCapture() const{
    return capturedPiece.has_value();
}

bool ClassicMove::isEnPassant() const{
    return isEnPassantFlag;
}

bool ClassicMove::isPawnPromotion() const{
    return isPawnPromotionFlag;
}

std::optional<Piece> ClassicMove::getPromotionChoice() const{
    return promotionChoice;
}

bool ClassicMove::isCastling() const{
    return isCastlingFlag;
}

std::unordered_set<std::size_t> ClassicMove::getCastlingRemovals() const{
    return castlingRemovals;
}

bool ClassicMove::isCheck() const{
    return isCheckFlag;
}

bool ClassicMove::isCheckmate() const{
    return isCheckmateFlag;
}

std::string ClassicMove::getNotation() const{
    return notation;
}