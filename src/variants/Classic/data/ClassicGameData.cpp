#include <stdexcept>
#include <sstream>
#include "FileConverter.h"
#include "variants/Classic/data/ClassicGameData.h"
#include "Board.h"
// TODO: recheck this one on correct initialization of castlingRights and kingsPositions
ClassicGameData::ClassicGameData(){
    fromFEN(FEN{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w AHah - 0 1"});
}

ClassicGameData::ClassicGameData(const FEN& fen){
    fromFEN(fen);
}

bool ClassicGameData::operator==(const ClassicGameData& other) const{
    return (board == other.board && history == other.history && castlingRights == other.castlingRights &&
            currentTurn == other.currentTurn && kingsPositions == other.kingsPositions &&
            possibleEnPassant == other.possibleEnPassant);
}

bool ClassicGameData::operator!=(const ClassicGameData& other) const{
    return !(*this == other);
}

Board& ClassicGameData::accessBoard(){
    return board;
}

const Board& ClassicGameData::getBoard() const{
    return board;
}

ClassicGameData& ClassicGameData::setBoard(const Board& newBoard){
    board = newBoard;
    return *this;
}

ClassicGameData& ClassicGameData::setBoard(Board&& newBoard){
    board = newBoard;
    return *this;
}

const std::vector<ClassicMoveRecord>& ClassicGameData::getHistory() const{
    return history;
}

ClassicGameData& ClassicGameData::appendHistory(const ClassicMoveRecord& moveRecord){
    history.push_back(moveRecord);
    return *this;
}

ClassicGameData& ClassicGameData::removeHistory(std::size_t number){
    if (number > history.size()){
        number = history.size();
    }
    history.erase(history.end() - static_cast<std::vector<ClassicMoveRecord>::difference_type>(number), history.end());
    return *this;
}

ClassicGameData& ClassicGameData::clearHistory(){
    history.clear();
    return *this;
}

ClassicMoveRecord ClassicGameData::popHistory(){
    if (history.empty()) { // TODO: think if it should throw this error or there is a better way around
        throw std::out_of_range{"No moves in history to pop."};
    }
    ClassicMoveRecord lastMove{history.back()};
    history.pop_back();
    return lastMove;
}

const CastlingRights& ClassicGameData::getCastlingRights() const{
    return castlingRights;
}

ClassicGameData& ClassicGameData::addCastling(Color side, std::size_t file){
    castlingRights.add(side, file);
    return *this;
}

ClassicGameData& ClassicGameData::removeCastling(Color side, std::size_t file){
    castlingRights.remove(side, file);
    return *this;
}

ClassicGameData& ClassicGameData::setCastling(Color side, const std::unordered_set<std::size_t>& rights){
    castlingRights.set(side, rights);
    return *this;
}

ClassicGameData& ClassicGameData::resetCastling(Color side){
    castlingRights.reset(side);
    return *this;
}

ClassicGameData& ClassicGameData::resetCastling(){
    castlingRights.reset();
    return *this;
}

Color ClassicGameData::getCurrentTurn() const{
    return currentTurn;
}

ClassicGameData& ClassicGameData::setCurrentTurn(Color color){
    currentTurn = color;
    return *this;
}

Position ClassicGameData::getKingPosition(Color color) const{
    return kingsPositions.at(color);
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

namespace{
    char toChar(PieceType type){
        switch (type){
        case PieceType::PAWN:   return 'P';
        case PieceType::KNIGHT: return 'N';
        case PieceType::BISHOP: return 'B';
        case PieceType::ROOK:   return 'R';
        case PieceType::QUEEN:  return 'Q';
        case PieceType::KING:   return 'K';
        default:
            std::stringstream errorMessage;
            errorMessage << "Unexpected PieceType: " << EnumConverter::toString(type);
            throw std::invalid_argument{errorMessage.str()};
        }
    }
    
    char toChar(const Piece& piece){
        if (piece.getColor() == Color::WHITE){
            return toChar(piece.getType());
        }
        else{
            return std::tolower(toChar(piece.getType()));
        }
    }

    std::string toFEN(const Board& board){
        std::string result{};
        result.reserve(board.getHeight() * board.getWidth());
        for (std::size_t rank{1}; rank < board.getHeight(); ++rank){
            std::size_t emptySquares{0};
            for (std::size_t file{1}; file < board.getWidth(); ++file){
                // TODO: add support for non-existing squares
                std::optional<Piece> currentPiece{board.getAt(Position{file, rank})};
                if (currentPiece){
                    if (emptySquares > 0){
                        result += std::to_string(emptySquares);
                        emptySquares = 0;
                    }
                    result.push_back(toChar(currentPiece.value()));
                }
                else{
                    ++emptySquares;
                }
            }
            if (emptySquares > 0){
                result += std::to_string(emptySquares);
            }
            if (rank != board.getHeight()){
                result.push_back('/');
            }
        }
        return result;
    }
}

FEN ClassicGameData::toFEN() const{
    std::string result{::toFEN(board)};
    result.push_back(' ');
    if (currentTurn == Color::WHITE){
        result.push_back('w');
    }
    else{
        result.push_back('b');
    }
    result.push_back(' ');
    if (castlingRights.isPossible(Color::WHITE)){
        for (std::size_t index : castlingRights.get(Color::WHITE)){
            result.push_back(std::toupper(fileToChar(index)));
        }
    }
    if (castlingRights.isPossible(Color::BLACK)){
        for (std::size_t index : castlingRights.get(Color::BLACK)){
            result.push_back(fileToChar(index));
        }
    }
    if (result.back() == ' '){
        result.push_back('-');
    }
    result.push_back(' ');
    if (possibleEnPassant){
        result.push_back(fileToChar(possibleEnPassant.value().getFile()));
        result += std::to_string(possibleEnPassant.value().getRank());
    }
    else{
        result.push_back('-');
    }
    result.push_back(' ');
    result += std::to_string(history.size());
    result.push_back(' ');
    result += std::to_string(history.size() / 2);
    return FEN(result);
}

ClassicGameData& ClassicGameData::fromFEN(const FEN& fen){
    std::stringstream FENboard{fen.getBoard()};
    std::vector<std::string> ranks;
    std::string rank;

    while (std::getline(FENboard, rank, '/')) {
        ranks.push_back(rank);
    }
    for (std::size_t i{0}; i < ranks.size(); ++i){
        std::size_t stringIndex{0}, boardIndex{0};
        while (stringIndex < ranks[i].size()){
            if (std::isdigit(ranks[i][stringIndex])){
                std::size_t emptySquares;
                if (stringIndex + 1 < ranks[i].size() && std::isdigit(ranks[i][stringIndex + 1])){
                    emptySquares = std::stoull(ranks[i].substr(stringIndex, 2));
                    ++stringIndex;
                }
                else{
                    emptySquares = std::stoull(ranks[i].substr(stringIndex, 1));
                }
                ++stringIndex;
                for (std::size_t j{0}; j < emptySquares; ++j){
                    board.clearAt(Position{board.getHeight(), i, boardIndex});
                    ++boardIndex;
                }
            }
            else{
                Position position{board.getHeight(), i, boardIndex};
                switch (ranks[i][stringIndex]){
                case 'P': board.setAt(position, Piece{Color::WHITE, PieceType::PAWN});   break;
                case 'N': board.setAt(position, Piece{Color::WHITE, PieceType::KNIGHT}); break;
                case 'B': board.setAt(position, Piece{Color::WHITE, PieceType::BISHOP}); break;
                case 'R': board.setAt(position, Piece{Color::WHITE, PieceType::ROOK});   break;
                case 'Q': board.setAt(position, Piece{Color::WHITE, PieceType::QUEEN});  break;
                case 'K': board.setAt(position, Piece{Color::WHITE, PieceType::KING});
                          kingsPositions[Color::WHITE] = position;
                          break;
                case 'p': board.setAt(position, Piece{Color::BLACK, PieceType::PAWN});   break;
                case 'n': board.setAt(position, Piece{Color::BLACK, PieceType::KNIGHT}); break;
                case 'b': board.setAt(position, Piece{Color::BLACK, PieceType::BISHOP}); break;
                case 'r': board.setAt(position, Piece{Color::BLACK, PieceType::ROOK});   break;
                case 'q': board.setAt(position, Piece{Color::BLACK, PieceType::QUEEN});  break;
                case 'k': board.setAt(position, Piece{Color::BLACK, PieceType::KING});
                          kingsPositions[Color::BLACK] = position;
                          break;
                default:
                    std::stringstream errorMessage;
                    errorMessage << "Unexpected symbol in FEN string: " << ranks[i][stringIndex];
                    throw std::invalid_argument{errorMessage.str()};
                }
                ++boardIndex;
                ++stringIndex;
            }
        }
    }

    history.clear();

    castlingRights.reset();
    for (const char file : fen.getCastlingRights()){
        // Black
        if (islower(file)){
            castlingRights.add(Color::BLACK, fileToIndex(file));
        }
        //White
        else{
            castlingRights.add(Color::WHITE, fileToIndex(file));
        }
    }

    currentTurn = fen.getColor();   

    std::string fenEnPassant{fen.getEnPassant()};
    if (fenEnPassant == "-"){
        possibleEnPassant = std::nullopt;
    }
    else{
        possibleEnPassant = Position{fileToIndex(fenEnPassant[0]), static_cast<std::size_t>(fenEnPassant[1] - '0')};
    }

    return *this;
}