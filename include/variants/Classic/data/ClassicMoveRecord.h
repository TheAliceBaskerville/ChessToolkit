#ifndef CLASSICMOVERECORD_H
#define CLASSICMOVERECORD_H

#include "FEN.h"
#include "variants/Classic/data/ClassicMove.h"

class ClassicMoveRecord{
private:
    ClassicMove move;
    FEN fen;
public:
    ClassicMoveRecord(const ClassicMove& move, const FEN& fen);
    ClassicMoveRecord(const ClassicMoveRecord&) = default;
    ClassicMoveRecord(ClassicMoveRecord&&) = default;
    ~ClassicMoveRecord() = default;

    ClassicMoveRecord& operator=(const ClassicMoveRecord&) = default;
    ClassicMoveRecord& operator=(ClassicMoveRecord&&) = default;
    bool operator==(const ClassicMoveRecord& other) const;
    bool operator!=(const ClassicMoveRecord& other) const;

    FEN getFEN() const;
    ClassicMove getMove() const;
};

#endif