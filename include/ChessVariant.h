#ifndef CHESSVARIANT_H
#define CHESSVARIANT_H

enum class ChessVariant{
    CLASSIC,
    CHESS960,
    MADHOUSE,
    ATOMIC,
    COUNT
};

namespace EnumConverter {
    inline std::string toString(ChessVariant variant){
        switch (variant) {
            case ChessVariant::CLASSIC:  return "CLASSIC";
            case ChessVariant::CHESS960: return "CHESS960";
            case ChessVariant::MADHOUSE: return "MADHOUSE";
            case ChessVariant::ATOMIC:   return "ATOMIC";
            case ChessVariant::COUNT:    return "COUNT";
            default: throw std::out_of_range{"Unexpected variant given."}; // TODO: think on better error message
        }
    }
};

#endif