#include "variants/Classic/data/ClassicMoveRecord.h"

ClassicMoveRecord::ClassicMoveRecord(const ClassicMove& move, const FEN& fen) : move{move}, fen{fen}{}

bool ClassicMoveRecord::operator==(const ClassicMoveRecord& other) const{return (move == other.move && fen == other.fen);}
bool ClassicMoveRecord::operator!=(const ClassicMoveRecord& other) const{return !(*this == other);}

FEN ClassicMoveRecord::getFEN() const{return fen;}
ClassicMove ClassicMoveRecord::getMove() const{return move;}