#ifndef CLASSICGAMEDATA_H
#define CLASSICGAMEDATA_H

#include "Board.h"
#include "variants/Classic/data/ClassicMoveRecord.h"
#include "CastlingRights.h"

class ClassicGameData{
private:
    Board board;
    std::vector<ClassicMoveRecord> history;
    CastlingRights castlingRights;
    Color currentTurn;
    std::unordered_map<Color, Position> kingsPositions;
    std::optional<Position> possibleEnPassant;
public:
    ClassicGameData();
    ClassicGameData(const FEN& fen);
    ClassicGameData(const ClassicGameData&) = default;
    ClassicGameData(ClassicGameData&&) = default;
    ~ClassicGameData() = default;

    ClassicGameData& operator=(const ClassicGameData&) = default;
    ClassicGameData& operator=(ClassicGameData&&) = default;
    bool operator==(const ClassicGameData& other) const;
    bool operator!=(const ClassicGameData& other) const;

    Board& accessBoard();
    const Board& getBoard() const;
    ClassicGameData& setBoard(const Board& newBoard);
    ClassicGameData& setBoard(Board&& newBoard);

    const std::vector<ClassicMoveRecord>& getHistory() const;
    ClassicGameData& appendHistory(const ClassicMoveRecord& moveRecord);
    ClassicGameData& removeHistory(std::size_t number);
    ClassicGameData& clearHistory();
    ClassicMoveRecord popHistory();

    const CastlingRights& getCastlingRights() const;
    ClassicGameData& addCastling(Color side, std::size_t file);
    ClassicGameData& removeCastling(Color side, std::size_t file);
    ClassicGameData& setCastling(Color side, const std::unordered_set<std::size_t>& rights);
    ClassicGameData& resetCastling(Color side);
    ClassicGameData& resetCastling();

    Color getCurrentTurn() const;
    ClassicGameData& setCurrentTurn(Color color);

    Position getKingPosition(Color color) const;
    ClassicGameData& setKingPosition(Color color, const Position& position);

    std::optional<Position> getEnPassant() const;
    bool canEnPassant() const;
    ClassicGameData& setEnPassant(const Position& position);
    ClassicGameData& clearEnPassant();

    FEN toFEN() const;
    ClassicGameData& fromFEN(const FEN& fen);
};

#endif