#ifndef FEN_H
#define FEN_H

#include <string>
#include <vector>
#include <optional>
#include "Piece.h"
#include "Position.h"

class FEN{
private:
    std::size_t width, height;
    std::string fen;
    std::vector<std::string> splitFEN() const;
    std::string joinFEN(const std::vector<std::string>& parts);
public:
    FEN(std::size_t width=8, std::size_t height=8);
    explicit FEN(const std::string& FEN);
    FEN(const FEN& other);
    FEN(FEN&& other) noexcept;
    ~FEN();

    FEN& operator=(const FEN& other);
    FEN& operator=(FEN&& other) noexcept;
    bool operator==(const FEN& other) const;
    bool operator!=(const FEN& other) const;

    std::string getRank(std::size_t number) const;
    Color getColor() const;
    std::string getCastlingRights() const;
    std::string getEnPassant() const;
    std::size_t getHalfmovesNumber() const;
    std::size_t getFullmovesNumber() const;

    FEN& setRank(std::size_t number, const std::string& rankString);
    FEN& setColor(Color color);
    FEN& setColor(const std::string& color);
    FEN& setCastlingRights(const std::string& castlingRights);
    FEN& setEnPassant(const std::string& possibleEnPassantTarget);
    FEN& setHalfmovesNumber(std::size_t halfmovesNumber);
    FEN& setFullmovesNumber(std::size_t fullmovesNumber);
    
    std::size_t getWidth() const;
    std::size_t getHeight() const;
    std::pair<std::size_t, std::size_t> getSize() const;

    bool isExist(const Position& position) const;
    bool isEmpty(const Position& position) const;
    std::optional<Piece> getAt(const Position& position) const;

    FEN& setAt(const Position& position, const Piece& piece);
    FEN& clearAt(const Position& position);
    FEN& removeAt(const Position& position);
    FEN& clear();
    
    FEN& fromFEN(const FEN& FEN);
    std::string str() const;
    
    static bool isValid(const std::string& FENstring);
};

#endif