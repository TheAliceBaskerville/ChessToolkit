#ifndef CLASSICGAMELOGIC_H
#define CLASSICGAMELOGIC_H

#include "IGameLogic.h"

class ClassicGameLogic : public IGameLogic{
private:
    const ChessVariant variant{ChessVariant::CLASSIC};
    std::unordered_set<Move> getPieceMoves(IGameData& data, const Position& position) const;
    std::unordered_set<Move> getLegalMoves(IGameData& data) const;
    std::unordered_set<Move> getLegalMoves(IGameData& data, Color side) const;
    // TODO: think on adding method that switch between black and white
public:
    explicit ClassicGameLogic();
    ~ClassicGameLogic() override;

    ChessVariant getVariant() const override;

    bool isValidMove(IGameData& data, const Move& move) const override;
    std::unordered_set<Move> getValidMoves(IGameData& data) const override;
    std::unordered_set<Move> getValidMoves(IGameData& data, const Position& position) const override;

    bool isUnderAttack(IGameData& data, const Position& position) const override;
    bool isUnderAttack(IGameData& data, const Position& position, Color side) const override;
    bool isCheck(IGameData& data) const override;
    bool isCheck(IGameData& data, Color side) const override;

    GameStatus getStatus(IGameData& data) const override;

    IGameData& makeMove(IGameData& data, const Move& move) const override;
    IGameData& undoMove(IGameData& data, std::size_t number=1) const override;

    std::unique_ptr<IGameLogic> clone() const override;
};

#endif