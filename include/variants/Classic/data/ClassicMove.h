#ifndef CLASSICMOVE_H
#define CLASSICMOVE_H

#include <optional>
#include <unordered_set>
#include "Position.h"
#include "Piece.h"

class ClassicMove{
private:
    Position start, end;
    Piece movedPiece;
    std::optional<Piece> capturedPiece;
    bool isEnPassantFlag, isPawnPromotionFlag, isCastlingFlag;
    std::optional<Piece> promotionChoice;
    std::unordered_set<std::size_t> castlingRemovals;
    bool isCheckFlag, isCheckmateFlag;
    std::string notation;
public:
    ClassicMove(const Position& start, const Position& end, const Piece& movedPiece, 
                const std::optional<Piece>& capturedPiece, bool isEnPassant, bool isPawnPromotion,
                bool isCastling, const std::optional<Piece>& promotionChoice,
                const std::unordered_set<std::size_t>& castlingRemovals, bool isCheckFlag,
                bool isCheckmateFlag, const std::string& notation);
    ClassicMove(const ClassicMove&) = default;
    ClassicMove(ClassicMove&&) = default;
    ~ClassicMove() = default;

    ClassicMove& operator=(const ClassicMove&) = default;
    ClassicMove& operator=(ClassicMove&&) = default;
    bool operator==(const ClassicMove& other) const;
    bool operator!=(const ClassicMove& other) const;

    Position getStart() const;
    Position getEnd() const;
    Piece getMovedPiece() const;
    std::optional<Piece> getCapturedPiece() const;
    bool isCapture() const;
    bool isEnPassant() const;
    bool isPawnPromotion() const;
    std::optional<Piece> getPromotionChoice() const;
    bool isCastling() const;
    std::unordered_set<std::size_t> getCastlingRemovals() const;
    bool isCheck() const;
    bool isCheckmate() const;
    std::string getNotation() const;
};

#endif