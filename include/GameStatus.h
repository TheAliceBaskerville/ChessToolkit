#ifndef GAMESTATUS_H
#define GAMESTATUS_H

enum class Status{
    ONGOING,
    VICTORY,
    DRAW,
    COUNT
};

enum class DetailedStatus{
    ONGOING,
    CHECKMATE,
    STALEMATE,
    THREEFOLD_REPETITION,
    INSUFFICIENT_MATERIAL,
    FIFTY_MOVES_RULE,
    COUNT
};

class GameStatus{
private:
    DetailedStatus status;
    Status getFromDetailed(DetailedStatus status) const;
public:
    GameStatus(DetailedStatus status);
    GameStatus(const GameStatus&) = default;
    GameStatus(GameStatus&&) noexcept = default;
    ~GameStatus() = default;

    GameStatus& operator=(const GameStatus&) = default;
    GameStatus& operator=(GameStatus&&) = default;
    bool operator==(const GameStatus& other) const;
    bool operator!=(const GameStatus& other) const;

    Status getStatus() const;
    DetailedStatus getDetailedType() const;

    GameStatus& setStatus(DetailedStatus newStatus);
};

#endif