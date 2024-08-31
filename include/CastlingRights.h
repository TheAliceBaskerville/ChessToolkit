#ifndef CASTLINGRIGHTS_H
#define CASTLINGRIGHTS_H

#include <unordered_set>
#include <unordered_map>
#include "Color.h"

class CastlingRights{
private:
    std::unordered_map<Color, std::unordered_set<int>> castlingFiles;
public:
    CastlingRights();
    ~CastlingRights();

    bool at(Color side, int file) const;
    std::unordered_set<int> get(Color side) const;
    bool isPossible(Color side) const;
    CastlingRights& add(Color side, int file);
    CastlingRights& remove(Color side, int file);
    CastlingRights& set(Color side, std::unordered_set<int> rights);
    CastlingRights& reset(Color side);
    CastlingRights& reset();
};

#endif