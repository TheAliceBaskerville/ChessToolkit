#ifndef CLASSICMOVECONSTRUCT_H
#define CLASSICMOVECONSTRUCT_H

#include <optional>
#include <functional> // For std::hash
#include "Position.h"
#include "Piece.h"

class ClassicMoveConstruct{
private:
    Position start, end;
    std::optional<Piece> promotionChoice;
public:
    ClassicMoveConstruct(const Position& start, const Position& end,
                         const std::optional<Piece> promotionChoice=std::nullopt);
    ClassicMoveConstruct(const ClassicMoveConstruct&) = default;
    ClassicMoveConstruct(ClassicMoveConstruct&&) = default;
    ~ClassicMoveConstruct() = default;

    ClassicMoveConstruct& operator=(const ClassicMoveConstruct&) = default;
    ClassicMoveConstruct& operator=(ClassicMoveConstruct&&) = default;
    bool operator==(const ClassicMoveConstruct& other) const;
    bool operator!=(const ClassicMoveConstruct& other) const;

    Position getStart() const;
    Position getEnd() const;
    std::optional<Piece> getPromotionChoice() const;
    bool isPawnPromotion() const;
};

namespace std{
    template<>
    struct hash<ClassicMoveConstruct>{
        std::size_t operator()(const ClassicMoveConstruct& move) const{
            std::size_t hashStart{std::hash<Position>()(move.getStart())};
            std::size_t hashEnd{std::hash<Position>()(move.getEnd())};
            std::size_t hashPromotion{0};
            if (move.isPawnPromotion()){
                hashPromotion = std::hash<Piece>()(move.getPromotionChoice().value());
            }

            return hashStart ^ (hashEnd << 1) ^ (hashPromotion << 2);
        }
    };
}

#endif