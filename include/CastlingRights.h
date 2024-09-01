#ifndef CASTLINGRIGHTS_H
#define CASTLINGRIGHTS_H

#include <unordered_set>
#include <unordered_map>
#include "Color.h"

class CastlingRights{
private:
    std::unordered_map<Color, std::unordered_set<std::size_t>> castlingFiles;
public:
    CastlingRights();
    ~CastlingRights();

    bool at(Color side, std::size_t file) const;
    std::unordered_set<std::size_t> get(Color side) const;
    bool isPossible(Color side) const;
    CastlingRights& add(Color side, std::size_t file);
    CastlingRights& remove(Color side, std::size_t file);
    CastlingRights& set(Color side, const std::unordered_set<std::size_t>& rights);
    CastlingRights& reset(Color side);
    CastlingRights& reset();
};

#endif