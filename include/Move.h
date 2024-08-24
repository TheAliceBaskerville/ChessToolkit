#ifndef MOVE_H
#define MOVE_H

#include <utility> // For std::pair
#include <optional>
#include "Piece.h"

class Move{
private:
    int startFile, startRank, endFile, endRank;
    bool isEnPassantFlag, isPawnPromotionFlag;
    std::optional<Piece> promotionChoice;
    Piece movedPiece;
    std::optional<Piece> capturedPiece;
public:
    Move(int startFile, int startRank, int endFile, int endRank,
         bool isEnPassant, bool isPawnPromotion, const std::optional<Piece>& promotionChoice,
         const Piece& movedPiece, const std::optional<Piece>& capturedPiece);
    ~Move();

    Move& operator=(const Move& other);
    bool operator==(const Move& other) const;
    bool operator!=(const Move& other) const;

    int getStartFile() const;
    int getStartRank() const;
    int getEndFile() const;
    int getEndRank() const;
    std::pair<int, int> getStart() const;
    std::pair<int, int> getEnd() const;

    bool isEnPassant() const;
    bool isPawnPromotion() const;
    std::optional<Piece> getPromotionChoice() const;

    Piece getMovedPiece() const;
    std::optional<Piece> getCapturedPiece() const;
    bool isCapture() const;
};

#endif