#include <stdexcept>
#include "ClassicGameData.h"
#include "MatrixBoard.h"

ClassicGameData::ClassicGameData() 
    : board{std::make_unique<MatrixBoard>()}, currentTurn{Color::WHITE}, possibleEnPassant{std::nullopt}{
    board->fromFEN(FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")); // TODO: think on loading defaults from somewhere
    castlingRights.set(Color::WHITE, {1, 8});
    castlingRights.set(Color::BLACK, {1, 8});
    kingsPositions = {
        {Color::WHITE, Position{5, 1}},
        {Color::BLACK, Position{5, 8}}
    };
}

ClassicGameData::ClassicGameData(const ClassicGameData& other)
    : board{other.board->clone()}, history{other.history}, castlingRights{other.castlingRights},
      currentTurn{other.currentTurn}, kingsPositions{other.kingsPositions}, possibleEnPassant{other.possibleEnPassant}{}

ClassicGameData::ClassicGameData(ClassicGameData&& other) noexcept
    : board{std::move(other.board)}, history{std::move(other.history)}, castlingRights{std::move(other.castlingRights)},
      currentTurn{other.currentTurn}, kingsPositions{std::move(other.kingsPositions)},
      possibleEnPassant{std::move(other.possibleEnPassant)}{}

ClassicGameData::~ClassicGameData(){}

ClassicGameData& ClassicGameData::operator=(const ClassicGameData& other){
    if (this == &other) { 
        return *this;
    }

    board = other.board->clone();
    history = other.history;
    castlingRights = other.castlingRights;
    currentTurn = other.currentTurn;
    kingsPositions = other.kingsPositions;
    possibleEnPassant = other.possibleEnPassant;

    return *this;
}

ClassicGameData& ClassicGameData::operator=(ClassicGameData&& other) noexcept{
    if (this == &other) { 
        return *this;
    }

    board = std::move(other.board);
    history = std::move(other.history);
    castlingRights = std::move(other.castlingRights);
    currentTurn = other.currentTurn;
    kingsPositions = std::move(other.kingsPositions);
    possibleEnPassant = std::move(other.possibleEnPassant);

    return *this;
}

IChessBoard& ClassicGameData::accessBoard(){
    return *board;
}

const IChessBoard& ClassicGameData::getBoard() const{
    return *board;
}

ClassicGameData& ClassicGameData::setBoard(std::unique_ptr<IChessBoard> board){ // TODO: rethink this one
    this->board = std::move(board);
    return *this;
}

ChessVariant ClassicGameData::getVariant() const{
    return variant;
}

const std::vector<Move>& ClassicGameData::getHistory() const{
    return history;
}

const CastlingRights& ClassicGameData::getCastlingRights() const{
    return castlingRights;
}

Color ClassicGameData::getCurrentTurn() const{
    return currentTurn;
}

Position ClassicGameData::getKingPosition(Color color) const{
    return kingsPositions.at(color);
}

ClassicGameData& ClassicGameData::appendHistory(const Move& move){
    history.push_back(move);
    return *this;
}

ClassicGameData& ClassicGameData::removeHistory(std::size_t number){
    if (number > history.size()){
        number = history.size();
    }
    history.erase(history.end() - static_cast<std::vector<Move>::difference_type>(number), history.end());
    return *this;
}

ClassicGameData& ClassicGameData::clearHistory(){
    history.clear();
    return *this;
}

Move ClassicGameData::popHistory(){
    if (history.empty()) {
        throw std::out_of_range{"No moves in history to pop."};
    }
    Move lastMove = history.back();
    history.pop_back();
    return lastMove;
}

ClassicGameData& ClassicGameData::addCastling(Color color, std::size_t file){
    castlingRights.add(color, file);
    return *this;
}

ClassicGameData& ClassicGameData::removeCastling(Color color, std::size_t file){
    castlingRights.remove(color, file);
    return *this;
}

ClassicGameData& ClassicGameData::setCastling(Color color, const std::unordered_set<std::size_t>& rights){
    castlingRights.set(color, rights);
    return *this;
}

ClassicGameData& ClassicGameData::resetCastling(Color color){
    castlingRights.reset(color);
    return *this;
}

ClassicGameData& ClassicGameData::resetCastling(){
    castlingRights.reset();
    return *this;
}

ClassicGameData& ClassicGameData::setCurrentTurn(Color color){
    currentTurn = color;
    return *this;
}

ClassicGameData& ClassicGameData::setKingPosition(Color color, const Position& position){
    kingsPositions[color] = position;
    return *this;
}

std::optional<Position> ClassicGameData::getEnPassant() const{
    return possibleEnPassant;
}

bool ClassicGameData::canEnPassant() const{
    return possibleEnPassant.has_value();
}

ClassicGameData& ClassicGameData::setEnPassant(const Position& position){
    possibleEnPassant = position;
    return *this;
}

ClassicGameData& ClassicGameData::clearEnPassant(){
    possibleEnPassant = std::nullopt;
    return *this;
}

std::unique_ptr<IGameData> ClassicGameData::clone() const{
    return std::make_unique<ClassicGameData>(*this);
}