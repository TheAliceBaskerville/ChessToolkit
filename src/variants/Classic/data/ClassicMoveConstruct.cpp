#include "variants/Classic/data/ClassicMoveConstruct.h"

ClassicMoveConstruct::ClassicMoveConstruct(const Position& start, const Position& end, 
                                           const std::optional<Piece> promotionChoice)
    : start{start}, end{end}, promotionChoice{promotionChoice}{}

bool ClassicMoveConstruct::operator==(const ClassicMoveConstruct& other) const{
    return (start == other.start && end == other.end && promotionChoice == other.promotionChoice);
}

bool ClassicMoveConstruct::operator!=(const ClassicMoveConstruct& other) const{
    return !(*this == other);
}

Position ClassicMoveConstruct::getStart() const{
    return start;
}

Position ClassicMoveConstruct::getEnd() const{
    return end;
}

std::optional<Piece> ClassicMoveConstruct::getPromotionChoice() const{
    return promotionChoice;
}

bool ClassicMoveConstruct::isPawnPromotion() const{
    return promotionChoice.has_value();
}