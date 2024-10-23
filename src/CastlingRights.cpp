#include "CastlingRights.h"

CastlingRights::CastlingRights(){
    castlingFiles[Color::WHITE] = {};
    castlingFiles[Color::BLACK] = {};
}

bool CastlingRights::operator==(const CastlingRights& other) const {
    if (castlingFiles.size() != other.castlingFiles.size()) {
        return false;
    }

    for (const auto& [side, files] : castlingFiles) {
        std::unordered_map<Color, std::unordered_set<std::size_t>>::const_iterator it = other.castlingFiles.find(side);
        if (it == other.castlingFiles.end()) {
            return false;
        }

        if (files != it->second) {
            return false;
        }
    }

    return true;
}

bool CastlingRights::operator!=(const CastlingRights& other) const{
    return !(*this == other);
}

bool CastlingRights::at(Color side, std::size_t file) const{
    return (castlingFiles.at(side).count(file) != 0); 
}

std::unordered_set<std::size_t> CastlingRights::get(Color side) const{
    return castlingFiles.at(side);
}

bool CastlingRights::isPossible(Color side) const{
    return !castlingFiles.at(side).empty();
}

CastlingRights& CastlingRights::add(Color side, std::size_t file){
    castlingFiles.at(side).insert(file);
    return *this;
}

CastlingRights& CastlingRights::remove(Color side, std::size_t file){
    castlingFiles.at(side).erase(file);
    return *this;
}

CastlingRights& CastlingRights::set(Color side, const std::unordered_set<std::size_t>& rights){
    castlingFiles.at(side) = rights;
    return *this;
}

CastlingRights& CastlingRights::reset(Color side){
    castlingFiles.at(side) = {};
    return *this;
}

CastlingRights& CastlingRights::reset(){
    for (auto& [side, files] : castlingFiles){
        files = {};
    }
    return *this;
}