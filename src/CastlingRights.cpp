#include "CastlingRights.h"

CastlingRights::CastlingRights(){
    castlingFiles[Color::WHITE] = {};
    castlingFiles[Color::BLACK] = {};
}

bool CastlingRights::at(Color color, int file) const{
    return castlingFiles.at(color).find(file) != castlingFiles.at(color).end(); 
}

bool CastlingRights::isPossible(Color color) const{
    return !castlingFiles.at(color).empty();
}

CastlingRights& CastlingRights::add(Color color, int file){
    castlingFiles.at(color).insert(file);
    return *this;
}

CastlingRights& CastlingRights::remove(Color color, int file){
    castlingFiles.at(color).erase(file);
    return *this;
}

CastlingRights& CastlingRights::set(Color color, std::set<int> rights){
    castlingFiles.at(color) = rights;
    return *this;
}

CastlingRights& CastlingRights::reset(Color color){
    castlingFiles.at(color) = {};
    return *this;
}

CastlingRights& CastlingRights::reset(){
    for (auto& [color, files] : castlingFiles){
        files = {};
    }
    return *this;
}