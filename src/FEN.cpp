#include <sstream>
#include <utility> // For std::move()
#include <map>
#include <set>
#include "FEN.h"

FEN::FEN(int width, int height) : width{width}, height{height}{
    std::stringstream result;
    for (int rank{0}; rank < height; ++rank){
        if (rank > 0){
            result << "/";
        }
        result << width;
    }
    result << " w - - - 0 0";
    fen = result.str();
}

FEN::FEN(const std::string& FEN){

}

FEN::FEN(const FEN& other) : width{other.width}, height{other.height}, fen{other.fen}{}
FEN::FEN(FEN&& other) noexcept : width{other.width}, height{other.height}, fen{std::move(other.fen)}{}
FEN::~FEN(){}

FEN& FEN::operator=(const FEN& other){
    if (this == &other){
        return *this;
    }
    width = other.width;
    height = other.height;
    fen = other.fen;
    return *this;
}

FEN& FEN::operator=(FEN&& other) noexcept{
    width = other.width;
    height = other.height;
    fen = std::move(other.fen);
    return *this;
}

bool FEN::operator==(const FEN& other) const{
    return (fen == other.fen);
}

bool FEN::operator!=(const FEN& other) const{
    return !(*this == other);
}

std::vector<std::string> FEN::splitFEN() const{
    std::vector<std::string> parts;
    std::stringstream fenStream{fen};
    std::string part;

    while (std::getline(fenStream, part, ' ')) {
        parts.push_back(part);
    }
    return parts;
}

std::string joinFEN(const std::vector<std::string>& parts){
    std::stringstream fenStream{};
    for (auto& part : parts){
        fenStream << part;
    }
    return fenStream.str();
}

std::string FEN::getRank(int number) const{
    if (number < 1 || number > height){
        std::stringstream errorMessage;
        errorMessage << "Rank number out of range: " << number;
        throw std::out_of_range{errorMessage.str()};
    }
    std::stringstream fenStream{fen};
    std::string rankString;
    for (int rank{0}; rank <= height - number; ++rank){
        std::getline(fenStream, rankString, '/');
    }
    return rankString;
}

Color FEN::getColor() const{
    static const std::map<std::string, Color> colorMap{
        {"w", Color::WHITE},
        {"b", Color::BLACK}
    };

    std::vector<std::string> parts{splitFEN()};
    return colorMap.at(parts[1]);
}

std::string FEN::getCastlingRights() const{
    std::vector<std::string> parts{splitFEN()};
    return parts[2];
}

std::string FEN::getEnPassant() const{
    std::vector<std::string> parts{splitFEN()};
    return parts[3];
}

int FEN::getHalfmovesNumber() const{
    std::vector<std::string> parts{splitFEN()};
    return std::stoi(parts[4]);
}

int FEN::getFullmovesNumber() const{
    std::vector<std::string> parts{splitFEN()};
    return std::stoi(parts[5]);
}

bool FEN::isValid(const std::string& FENstring){ //TODO: normal automate implementation
    std::stringstream fenStream{FENstring};
    std::string fenBlock;
    std::getline(fenStream, fenBlock, ' '); // asquiring board itself
    int slashPosition{fenBlock.find("/")};
    if (slashPosition == std::string::npos){
        return false;
    }
    int rankLength{0}, currentPosition{0};
    // while (currentPosition < slashPosition){
    //     switch (fenBlock[currentPosition])
    //     {
    //     case /* constant-expression */:
    //         /* code */
    //         break;
        
    //     default:
    //         break;
    //     }
    // }
    return true;
}

FEN& FEN::setRank(int number, const std::string& rankString){
    if (number < 1 || number > height){
        std::stringstream errorMessage;
        errorMessage << "Rank number out of range: " << number;
        throw std::out_of_range{errorMessage.str()};
    }
    // TODO: add rankString valiadtion here
    int index;
    for (int count{0}; count < number; ++count){
        index = fen.find("/");
    }
    fen.insert(index, rankString);
    return *this;
}

FEN& FEN::setColor(Color color){
    static const std::map<Color, std::string> colorMap{
        {Color::WHITE, "w"},
        {Color::BLACK, "b"}
    };
    std::vector<std::string> parts = splitFEN();
    parts[1] = colorMap.at(color);
    fen = joinFEN(parts);
    return *this;
}

FEN& FEN::setColor(const std::string& color){
    static const std::set<std::string> possibleColors{"b", "w"};
    if (possibleColors.find(color) == possibleColors.end()){
        std::stringstream errorMessage;
        // TODO: think on automating this string generation from possibleColors
        errorMessage << "Invalid colon given: " << color << ", \"b\" or \"w\" expected";
        throw std::invalid_argument{errorMessage.str()};
    }
    std::vector<std::string> parts = splitFEN();
    parts[1] = color;
    fen = joinFEN(parts);
    return *this;
}

FEN& FEN::setCastlingRights(const std::string& castlingRights){
    static const std::set<char> possibleRights{'k', 'K', 'q', 'Q', '-'};

    if (castlingRights.length() < 1 || castlingRights.length() > 2){
        std::stringstream errorMessage;
        errorMessage << "Invalid size of castlingRights: " << castlingRights.length() << " (" << castlingRights << ")";
        throw std::out_of_range{errorMessage.str()};
    }
    if (possibleRights.find(castlingRights[0]) == possibleRights.end()){ // TODO: think on how to validate castling rights
        std::stringstream errorMessage;
        errorMessage << "Invalid castling rights for white: " << castlingRights.length() << " (" << castlingRights << ")";
        throw std::invalid_argument{errorMessage.str()};
    } 
    std::vector<std::string> parts = splitFEN();
    parts[2] = castlingRights;
    fen = joinFEN(parts);
    return *this;
}

FEN& FEN::setEnPassant(const std::string& possibleEnPassantTarget){ // TODO: finish this one
    std::vector<std::string> parts = splitFEN();
    parts[3] = possibleEnPassantTarget;
    fen = joinFEN(parts);
    return *this;
}

FEN& FEN::setHalfmovesNumber(int halfmovesNumber){
    // TODO: implement this one
}

FEN& FEN::setFullmovesNumber(int fullmovesNumber){
    // TODO: implement this one
}

int FEN::getWidth() const{
    // TODO: implement this one
}

int FEN::getHeight() const{
    // TODO: implement this one
}

std::pair<int, int> FEN::getSize() const{
    // TODO: implement this one
}

bool FEN::isExist(int file, int rank) const{
    // TODO: implement this one
}

bool FEN::isEmpty(int file, int rank) const{
    // TODO: implement this one
}

std::optional<Piece> FEN::getAt(int file, int rank) const{
    // TODO: implement this one
}

FEN& FEN::setAt(int file, int rank, const Piece& piece){
    // TODO: implement this one
}

FEN& FEN::clearAt(int file, int rank){
    // TODO: implement this one
}

FEN& FEN::removeAt(int file, int rank){
    // TODO: implement this one
}

FEN& FEN::clear(){
    // TODO: implement this one
}

std::string FEN::str() const{
    return fen;
}

FEN& FEN::fromFEN(const FEN& FEN){
    // TODO: implement this one
}