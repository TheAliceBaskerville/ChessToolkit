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

namespace std {
    template<>
    struct hash<Move> {
        std::size_t operator()(const Move& move) const {
            std::size_t hashStart{std::hash<Position>()(move.getStart())};
            std::size_t hashEnd{std::hash<Position>()(move.getEnd())};
            std::size_t hashEnPassant{std::hash<bool>()(move.isEnPassant())};
            std::size_t hashPawnPromotion{std::hash<bool>()(move.isPawnPromotion())};
            std::size_t hashMovedPiece{std::hash<std::optional<Piece>>()(move.getMovedPiece())};
            std::size_t hashCapturedPiece{std::hash<std::optional<Piece>>()(move.getCapturedPiece())};

            return hashStart ^ (hashEnd << 1) ^ (hashEnPassant << 2) ^ 
                   (hashPawnPromotion << 3) ^ (hashMovedPiece << 4) ^ (hashCapturedPiece << 5);
        }
    };
}

#endif