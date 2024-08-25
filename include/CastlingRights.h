#ifndef CASTLINGRIGHTS_H
#define CASTLINGRIGHTS_H

#include <set>
#include <map>
#include "Color.h"

class CastlingRights{
private:
    std::map<Color, std::set<int>> castlingFiles;
public:
    CastlingRights();
    // Think about constructing from string

    bool at(Color color, int file) const;
    bool isPossible(Color color) const;
    CastlingRights& add(Color color, int file);
    CastlingRights& set(Color color, std::set<int> rights);
    CastlingRights& reset(Color color);
    CastlingRights& reset();
};

#endif