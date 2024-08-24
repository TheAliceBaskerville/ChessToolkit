#ifndef FEN_H
#define FEN_H

#include <string>
#include <vector>
#include <optional>
#include "Piece.h"

class FEN{
private:
    std::string fen;
    int width, height;
    std::vector<std::string> splitFEN() const;
    std::string joinFEN(const std::vector<std::string>& parts);
public:
    FEN(int width=8, int height=8);
    explicit FEN(const std::string& FEN);
    FEN(const FEN& other);
    FEN(FEN&& other) noexcept;
    ~FEN();

    FEN& operator=(const FEN& other);
    FEN& operator=(FEN&& other) noexcept;
    bool operator==(const FEN& other) const;
    bool operator!=(const FEN& other) const;

    std::string getRank(int number) const;
    Color getColor() const;
    std::string getCastlingRights() const;
    std::string getEnPassant() const;
    int getHalfmovesNumber() const;
    int getFullmovesNumber() const;

    FEN& setRank(int number, const std::string& rankString);
    FEN& setColor(Color color);
    FEN& setColor(const std::string& color);
    FEN& setCastlingRights(const std::string& castlingRights);
    FEN& setEnPassant(const std::string& possibleEnPassantTarget);
    FEN& setHalfmovesNumber(int halfmovesNumber);
    FEN& setFullmovesNumber(int fullmovesNumber);
    
    int getWidth() const;
    int getHeight() const;
    std::pair<int, int> getSize() const;

    bool isExist(int file, int rank) const;
    bool isEmpty(int file, int rank) const;
    std::optional<Piece> getAt(int file, int rank) const;

    FEN& setAt(int file, int rank, const Piece& piece);
    FEN& clearAt(int file, int rank);
    FEN& removeAt(int file, int rank);
    FEN& clear();
    
    FEN& fromFEN(const FEN& FEN);
    std::string str() const;
    
    static bool isValid(const std::string& FENstring);
};

#endif