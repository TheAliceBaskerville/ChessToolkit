#include "CastlingRights.h"

CastlingRights::CastlingRights(){
    castlingFiles[Color::WHITE] = {};
    castlingFiles[Color::BLACK] = {};
}

CastlingRights::~CastlingRights(){}

bool CastlingRights::at(Color side, int file) const{
    return (castlingFiles.at(side).count(file) != 0); 
}

std::unordered_set<int> CastlingRights::get(Color side) const{
    return castlingFiles.at(side);
}

bool CastlingRights::isPossible(Color side) const{
    return !castlingFiles.at(side).empty();
}

CastlingRights& CastlingRights::add(Color side, int file){
    castlingFiles.at(side).insert(file);
    return *this;
}

CastlingRights& CastlingRights::remove(Color side, int file){
    castlingFiles.at(side).erase(file);
    return *this;
}

CastlingRights& CastlingRights::set(Color side, std::unordered_set<int> rights){
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