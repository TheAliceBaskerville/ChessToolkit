#ifndef MOVE_H
#define MOVE_H

#include <unordered_set>
#include <optional>
#include "Position.h"
#include "Piece.h"

class Move{ // TODO: .getNotation()
private:
    Position start, end;
    bool isEnPassantFlag, isPawnPromotionFlag, isCastlingFlag;
    std::optional<Piece> promotionChoice;
    std::optional<Piece> movedPiece, capturedPiece;
    std::unordered_set<std::size_t> castlingRemovals;
public:
    Move(const Position& start, const Position& end, bool isEnPassant, bool isPawnPromotion, bool isCastling,
         const std::optional<Piece>& promotionChoice, const std::optional<Piece>& movedPiece,
         const std::optional<Piece>& capturedPiece, const std::unordered_set<std::size_t>& castlingRemovals);
    Move(const Move& other);
    Move(Move&& other);
    ~Move();

    Move& operator=(const Move& other);
    Move& operator=(Move&& other);
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

    std::unordered_set<std::size_t> getCastlingRemovals() const;
    bool isCastling() const;
};

namespace std {
    template<>
    struct hash<Move> {
        std::size_t operator()(const Move& move) const {
            std::size_t hashStart{std::hash<Position>()(move.getStart())};
            std::size_t hashEnd{std::hash<Position>()(move.getEnd())};
            std::size_t hashEnPassant{std::hash<bool>()(move.isEnPassant())};
            std::size_t hashCastling{std::hash<bool>()(move.isCastling())};
            std::size_t hashPawnPromotion{std::hash<bool>()(move.isPawnPromotion())};

            std::size_t hashPromotionChoice{0};
            if (move.isPawnPromotion()){
                hashPromotionChoice = std::hash<Piece>()(move.getPromotionChoice().value());
            }
            std::size_t hashMovedPiece{0};
            if (move.hasMovedPiece()){
                hashMovedPiece = std::hash<Piece>()(move.getMovedPiece().value());
            }
            std::size_t hashCapturedPiece{0};
            if (move.isCapture()){
                hashCapturedPiece = std::hash<Piece>()(move.getCapturedPiece().value());
            }

            // "XOR and mix" for std::unordered_set<std::size_t>
            std::size_t hashCastlingRemovals{0};
            for (const std::size_t& item : move.getCastlingRemovals()) {
                hashCastlingRemovals ^= std::hash<std::size_t>()(item) + 0x9e3779b9 + // "Golden ratio"
                                        (hashCastlingRemovals << 6) + (hashCastlingRemovals >> 2);
            }

            return hashStart ^ (hashEnd << 1) ^ (hashEnPassant << 2) ^ (hashCastling << 3) ^
                   (hashPawnPromotion << 4) ^ (hashPromotionChoice << 5) ^ (hashMovedPiece << 6) ^
                   (hashCapturedPiece << 7) ^ (hashCastlingRemovals << 8);
        }
    };
}

#endif