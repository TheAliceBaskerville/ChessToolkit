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
    Status status;
    DetailedStatus detailedStatus;
    Status getFromDetailed(DetailedStatus detailedStatus);
public:
    GameStatus(DetailedStatus detailedStatus);
    ~GameStatus();

    GameStatus& operator=(const GameStatus& other);
    bool operator==(const GameStatus& other) const;
    bool operator!=(const GameStatus& other) const;

    Status getStatus() const;
    DetailedStatus getDetailedType() const;

    GameStatus& setStatus(DetailedStatus newStatus);
};

#endif