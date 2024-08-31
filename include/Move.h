#ifndef MOVE_H
#define MOVE_H

#include <optional>
#include "Position.h"
#include "Piece.h"

class Move{
private:
    Position start, end;
    bool isEnPassantFlag, isPawnPromotionFlag;
    std::optional<Piece> promotionChoice;
    std::optional<Piece> movedPiece, capturedPiece;
public:
    Move(const Position& start, const Position& end, bool isEnPassant, bool isPawnPromotion, 
         const std::optional<Piece>& promotionChoice, const std::optional<Piece>& movedPiece,
         const std::optional<Piece>& capturedPiece);
    ~Move();

    Move& operator=(const Move& other);
    bool operator==(const Move& other) const;
    bool operator!=(const Move& other) const;

    Position getStart() const;
    Position getEnd() const;

    bool isEnPassant() const;
    bool isPawnPromotion() const;
    std::optional<Piece> getPromotionChoice() const;

    std::optional<Piece> getMovedPiece() const;
    std::optional<Piece> getCapturedPiece() const;
    bool isCapture() const;
    bool hasMovedPiece() const;
};

#endif