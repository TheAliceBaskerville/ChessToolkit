#ifndef COLOR_H
#define COLOR_H

#include <stdexcept>
#include <string>

enum class Color{
    BLACK,
    WHITE,
    COUNT
};

inline Color switchColor(Color color){
    return color == Color::BLACK ? Color::WHITE : Color::BLACK;
}

namespace EnumConverter{
    inline std::string toString(Color color){
        switch (color) {
            case Color::BLACK: return "BLACK";
            case Color::WHITE: return "WHITE";
            case Color::COUNT: return "COUNT";
            default: throw std::out_of_range{"Unexpected Color given."};
        }
    }
}

#endif