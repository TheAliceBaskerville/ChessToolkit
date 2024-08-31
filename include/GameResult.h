#ifndef GAMERESULT_H
#define GAMERESULT_H

#include <variant>

class GameResult{
public:
    enum class Status{
        ONGOING,
        VICTORY,
        DRAW,
        COUNT
    };

    // TODO: refactor into Advanced status instead
    enum class VictoryType{ // TODO: think about better way to express someone's victory
        CHECKMATE,
        RESIGNATION,
        TIMEOUT,
        COUNT
    };

    enum class DrawType{
        STALEMATE,
        THREEFOLD_REPETITION,
        INSUFFICIENT_MATERIAL,
        FIFTY_MOVES_RULES,
        COUNT
    };
private:
    Status status;
    std::variant<VictoryType, DrawType, std::monostate> statusType;
public:
    GameResult();
    GameResult(VictoryType type);
    GameResult(DrawType draw);
    ~GameResult();

    GameResult& operator=(const GameResult& other);
    bool operator==(const GameResult& other) const;
    bool operator!=(const GameResult& other) const;

    Status getStatus() const;
    std::variant<VictoryType, DrawType, std::monostate> getStatusType() const;

    GameResult& setOngoing();
    GameResult& setStatusType(VictoryType type);
    GameResult& setStatusType(DrawType type);
};

#endif