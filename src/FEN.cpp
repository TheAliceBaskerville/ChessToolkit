#include <sstream>
#include <utility> // For std::move()
#include <map>
#include <set>
#include "FEN.h"

FEN::FEN(std::size_t width, std::size_t height) : width{width}, height{height}{
    // TODO: think on fillers for default variant
    std::stringstream result;
    for (std::size_t rank{0}; rank < height; ++rank){
        if (rank > 0){
            result << "/";
        }
        result << width;
    }
    result << " w - - - 0 0";
    fen = result.str();
}

FEN::FEN(const std::string& fen){
    this->fen = fen;
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

std::string FEN::joinFEN(const std::vector<std::string>& parts){
    std::stringstream fenStream{};
    for (auto& part : parts){
        fenStream << part;
    }
    return fenStream.str();
}

std::string FEN::getBoard() const{
    std::vector<std::string> parts{splitFEN()};
    return parts[0];
}

std::string FEN::getRank(std::size_t number) const{
    if (number < 1 || number > height){
        std::stringstream errorMessage;
        errorMessage << "Rank number out of range: " << number;
        throw std::out_of_range{errorMessage.str()};
    }
    std::stringstream fenStream{fen};
    std::string rankString;
    for (std::size_t rank{0}; rank <= height - number; ++rank){
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

std::size_t FEN::getHalfmovesNumber() const{
    std::vector<std::string> parts{splitFEN()};
    return std::stoull(parts[4]);
}

std::size_t FEN::getFullmovesNumber() const{
    std::vector<std::string> parts{splitFEN()};
    return std::stoull(parts[5]);
}

bool FEN::isValid(const std::string& FENstring){ //TODO: normal automate implementation
    std::stringstream fenStream{FENstring};
    std::string fenBlock;
    std::getline(fenStream, fenBlock, ' '); // asquiring board itself
    std::size_t slashPosition{fenBlock.find("/")};
    if (slashPosition == std::string::npos){
        return false;
    }
    std::size_t rankLength{0}, currentPosition{0};
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

FEN& FEN::setRank(std::size_t number, const std::string& rankString){
    if (number < 1 || number > height){
        std::stringstream errorMessage;
        errorMessage << "Rank number out of range: " << number;
        throw std::out_of_range{errorMessage.str()};
    }
    // TODO: add rankString valiadtion here
    std::size_t index;
    for (std::size_t count{0}; count < number; ++count){
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

FEN& FEN::setHalfmovesNumber(std::size_t halfmovesNumber){
    return *this;
    // TODO: implement this one
}

FEN& FEN::setFullmovesNumber(std::size_t fullmovesNumber){
    return *this;
    // TODO: implement this one
}

std::size_t FEN::getWidth() const{
    return 8;
    // TODO: implement this one
}

std::size_t FEN::getHeight() const{
    return 8;
    // TODO: implement this one
}

std::pair<std::size_t, std::size_t> FEN::getSize() const{
    return {8, 8};
    // TODO: implement this one
}

bool FEN::isExist(const Position& position) const{
    return false;
    // TODO: implement this one
}

bool FEN::isEmpty(const Position& position) const{
    return false;
    // TODO: implement this one
}

std::optional<Piece> FEN::getAt(const Position& position) const{
    return std::nullopt;
    // TODO: implement this one
}

FEN& FEN::setAt(const Position& position, const Piece& piece){
    return *this;
    // TODO: implement this one
}

FEN& FEN::clearAt(const Position& position){
    return *this;
    // TODO: implement this one
}

FEN& FEN::removeAt(const Position& position){
    return *this;
    // TODO: implement this one
}

FEN& FEN::clear(){
    return *this;
    // TODO: implement this one
}

std::string FEN::str() const{
    return fen;
}