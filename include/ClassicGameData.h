#ifndef CLASSICGAMEDATA_H
#define CLASSICGAMEDATA_H

#include <memory>
#include "IGameData.h"
#include "CastlingRights.h"

class ClassicGameData : public IGameData{
private:
    const ChessVariant variant{ChessVariant::CLASSIC};
    std::unique_ptr<IChessBoard> board;
    std::vector<Move> history;
    CastlingRights castlingRights;
    Color currentTurn;
    std::unordered_map<Color, Position> kingsPositions;
    std::optional<Position> possibleEnPassant;
public:
    explicit ClassicGameData();
    ClassicGameData(const ClassicGameData& other);
    ClassicGameData(ClassicGameData&& other) noexcept;
    ~ClassicGameData() override;

    ClassicGameData& operator=(const ClassicGameData& other);
    ClassicGameData& operator=(ClassicGameData&& other) noexcept;

    IChessBoard& accessBoard() override;
    const IChessBoard& getBoard() const override;
    ClassicGameData& setBoard(std::unique_ptr<IChessBoard> board) override;

    ChessVariant getVariant() const override;

    const std::vector<Move>& getHistory() const override;
    ClassicGameData& appendHistory(const Move& move) override;
    ClassicGameData& removeHistory(std::size_t number=1) override;
    ClassicGameData& clearHistory() override;
    Move popHistory() override;

    const CastlingRights& getCastlingRights() const;
    ClassicGameData& addCastling(Color color, std::size_t file);
    ClassicGameData& removeCastling(Color color, std::size_t file);
    ClassicGameData& setCastling(Color color, const std::unordered_set<std::size_t>& rights);
    ClassicGameData& resetCastling(Color color);
    ClassicGameData& resetCastling();

    Color getCurrentTurn() const override;
    ClassicGameData& setCurrentTurn(Color currentTurn) override;

    ClassicGameData& setKingPosition(Color color, const Position& position);
    Position getKingPosition(Color color) const;

    std::optional<Position> getEnPassant() const;
    bool canEnPassant() const;
    ClassicGameData& setEnPassant(const Position& position);
    ClassicGameData& clearEnPassant();

    std::unique_ptr<IGameData> clone() const override;
};

#endif