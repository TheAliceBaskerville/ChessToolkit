#include "CastlingRights.h"

CastlingRights::CastlingRights(){
    castlingFiles[Color::WHITE] = {};
    castlingFiles[Color::BLACK] = {};
}

CastlingRights::~CastlingRights(){}

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