#include <utility> // For std::move()
#include <stdexcept>
#include <sstream> // For string formatting
#include "MatrixBoard.h"

MatrixBoard::Square::Square(bool isExist) : 
    isExistFlag{isExist}, isEmptyFlag{true}, piece{Color::WHITE, PieceType::PAWN}{}
MatrixBoard::Square::Square(const Piece& piece) : 
    isExistFlag{true}, isEmptyFlag{false}, piece{piece}{}
MatrixBoard::Square::~Square(){}

bool MatrixBoard::Square::isExist() const {return isExistFlag;}
bool MatrixBoard::Square::isEmpty() const {return isEmptyFlag;}
const Piece& MatrixBoard::Square::getPiece() const {
    if (!isExistFlag){
        throw std::invalid_argument{"Trying to get piece from a square that does not exist."};
    }
    if (isEmptyFlag){
        throw std::invalid_argument{"Trying to get piece from a square that is empty."};
    }
    return piece;
}

MatrixBoard::Square& MatrixBoard::Square::setExist(bool isExistFlag){this->isExistFlag = isExistFlag; return *this;}
MatrixBoard::Square& MatrixBoard::Square::setEmpty(bool isEmptyFlag){this->isEmptyFlag = isEmptyFlag; return *this;}
MatrixBoard::Square& MatrixBoard::Square::setPiece(const Piece& piece){
    if (!isExistFlag){
        throw std::invalid_argument{"Trying to set piece to a square that does not exist."};
    }
    this->piece = piece; 
    return *this;
}

bool MatrixBoard::Square::operator==(const Square& other) const{
    return (isExistFlag == other.isExistFlag && isEmptyFlag == other.isEmptyFlag && piece == other.piece);
}
bool MatrixBoard::Square::operator!=(const Square& other) const{return !(*this==other);}

MatrixBoard::MatrixBoard(int height, int width) : width{width}, height{height}{
    if (width < 0){
        std::stringstream errorMessage;
        errorMessage << "Width is out of range, given: " << width;
        throw std::out_of_range{errorMessage.str()};
    }
    if (height < 0){
        std::stringstream errorMessage;
        errorMessage << "Height is out of range, given: " << height;
        throw std::out_of_range{errorMessage.str()};
    }
    board.resize(height, std::vector<Square>(width, Square(true)));
    for (int rank{0}; rank < height; ++rank){
        for (int file{0}; file < width; ++file){
            board[rank][file] = Square(true);
        }
    }
}

MatrixBoard::MatrixBoard(const FEN& FEN){
    fromFEN(FEN);
}

MatrixBoard::MatrixBoard(const MatrixBoard& other)
    : width{other.width}, height{other.height}, board{other.width, std::vector<Square>{other.height}}{
    for (int rank{0}; rank < height; ++rank) {
        std::copy(other.board[rank].begin(), other.board[rank].end(), board[rank].begin());
    }
}

MatrixBoard::MatrixBoard(MatrixBoard&& other) noexcept
    : width{other.width}, height{other.height}, board{std::move(other.board)} {}

MatrixBoard::~MatrixBoard(){}

MatrixBoard& MatrixBoard::operator=(const MatrixBoard& other){
    if (this == &other){
        return *this;
    }
    width = other.width;
    height = other.height;

    board.resize(other.height);
    for (auto& row : board){
        row.resize(other.width);
    }

    for (int rank{0}; rank < height; ++rank){
        for (int file{0}; file < width; ++file){
            board[rank][file] = other.board[rank][file];
        }
    }
    return *this;
}

MatrixBoard& MatrixBoard::operator=(MatrixBoard&& other) noexcept{
    width = other.width;
    height = other.height;
    board = std::move(other.board);
    return *this;
}

bool MatrixBoard::operator==(const MatrixBoard& other) const{
    if (width != other.width || height != other.height)
        return false;

    for (int rank{0}; rank < height; ++rank){
        for (int file{0}; file < width; ++file){
            if (board[rank][file] != other.board[rank][file]){
                return false;
            }
        }
    }
    return true;
}

bool MatrixBoard::operator!=(const MatrixBoard& other) const{
    return !(*this == other);
}

std::pair<int, int> MatrixBoard::notationToIndex(int file, int rank) const{
    if (file < 1 || file > width){
        std::stringstream errorMessage;
        errorMessage << "File is out of range: " << file;
        throw std::out_of_range{errorMessage.str()};
    }
    if (rank < 1 || rank > height){
        std::stringstream errorMessage;
        errorMessage << "Rank is out of range: " << rank;
        throw std::out_of_range{errorMessage.str()};
    }
    return {file - 1, height - rank};
}

std::pair<int, int> MatrixBoard::notationToIndex(const std::pair<int, int>& notation) const{
    return notationToIndex(notation.first, notation.second);
}

int MatrixBoard::getWidth() const{
    return width;
}

int MatrixBoard::getHeight() const{
    return height;
}

std::pair<int, int> MatrixBoard::getSize() const{
    return {height, width};
}

bool MatrixBoard::isExist(int file, int rank) const{
    std::pair<int, int> indexes = notationToIndex(file, rank);
    return board[indexes.first][indexes.second].isExist();
}

bool MatrixBoard::isEmpty(int file, int rank) const{
    std::pair<int, int> indexes = notationToIndex(file, rank);
    return board[indexes.first][indexes.second].isEmpty();
}

std::optional<Piece> MatrixBoard::getAt(int file, int rank) const{
    std::pair<int, int> indexes = notationToIndex(file, rank);
    if (!board[indexes.first][indexes.second].isExist() || board[indexes.first][indexes.second].isEmpty())
        return std::nullopt;
    return std::optional(board[indexes.first][indexes.second].getPiece());
}

MatrixBoard& MatrixBoard::setAt(int file, int rank, const Piece& piece){
    std::pair<int, int> indexes = notationToIndex(file, rank);
    if (!board[indexes.first][indexes.second].isExist()){
        std::stringstream errorMessage;
        errorMessage << "(" << file << ", " << rank << ") square does not exist."; // TODO: map file to a letter for better output
        throw std::invalid_argument{errorMessage.str()};
    }
    board[indexes.first][indexes.second].setPiece(piece);
    board[indexes.first][indexes.second].setEmpty(false);
    return *this;
}

MatrixBoard& MatrixBoard::clearAt(int file, int rank){
    std::pair<int, int> indexes = notationToIndex(file, rank);
    if (!board[indexes.first][indexes.second].isExist()){
        std::stringstream errorMessage;
        errorMessage << "(" << file << ", " << rank << ") square does not exist."; // TODO: map file to a letter for better output
        throw std::invalid_argument{errorMessage.str()};
    }
    board[indexes.first][indexes.second].setEmpty(true);
    return *this;
}

MatrixBoard& MatrixBoard::removeAt(int file, int rank){
    std::pair<int, int> indexes = notationToIndex(file, rank);
    board[indexes.first][indexes.second].setExist(false);
    return *this;
}

MatrixBoard& MatrixBoard::clear(){
    for (int rank{0}; rank < height; ++rank){
        for (int file{0}; file < width; ++file){
            if (board[rank][file].isExist())
                board[rank][file].setEmpty(true);
        }
    }
    return *this;
}

MatrixBoard& MatrixBoard::fromFEN(const FEN& fen){
    if (fen.getSize() != std::pair{height, width}){
        std::stringstream errorMessage;
        errorMessage << "Size mismatch between FEN and board dimensions, given {" << \
        fen.getHeight() << ", " << fen.getWidth() << "}, expected {" << height << ", " << width << "}";
        throw std::invalid_argument{errorMessage.str()};
    }
    std::stringstream FENboard{fen.str().substr(0, fen.str().find(' '))};
    std::vector<std::string> ranks;
    std::string rank;

    while (std::getline(FENboard, rank, '/')) {
        ranks.push_back(rank);
    }
    for (int i{0}; i < ranks.size(); ++i){
        int stringIndex{0}, boardIndex{0};
        while (stringIndex < ranks[i].size()){
            if (std::isdigit(ranks[i][stringIndex])){
                int emptySquares;
                if (stringIndex + 1 < ranks[i].size() && std::isdigit(ranks[i][stringIndex + 1])){
                    emptySquares = std::stoi(ranks[i].substr(stringIndex, 2));
                    ++stringIndex;
                }
                else{
                    emptySquares = std::stoi(ranks[i].substr(stringIndex, 1));
                }
                ++stringIndex;
                for (int j{0}; j < emptySquares; ++j){
                    board[i][boardIndex] = Square(true);
                    ++boardIndex;
                }
            }
            else{
                switch (ranks[i][stringIndex]){
                case 'P': board[i][boardIndex] = Square(Piece(Color::WHITE, PieceType::PAWN));   break;
                case 'N': board[i][boardIndex] = Square(Piece(Color::WHITE, PieceType::KNIGHT)); break;
                case 'B': board[i][boardIndex] = Square(Piece(Color::WHITE, PieceType::BISHOP)); break;
                case 'R': board[i][boardIndex] = Square(Piece(Color::WHITE, PieceType::ROOK));   break;
                case 'Q': board[i][boardIndex] = Square(Piece(Color::WHITE, PieceType::QUEEN));  break;
                case 'K': board[i][boardIndex] = Square(Piece(Color::WHITE, PieceType::KING));   break;
                case 'p': board[i][boardIndex] = Square(Piece(Color::BLACK, PieceType::PAWN));   break;
                case 'n': board[i][boardIndex] = Square(Piece(Color::BLACK, PieceType::KNIGHT)); break;
                case 'b': board[i][boardIndex] = Square(Piece(Color::BLACK, PieceType::BISHOP)); break;
                case 'r': board[i][boardIndex] = Square(Piece(Color::BLACK, PieceType::ROOK));   break;
                case 'q': board[i][boardIndex] = Square(Piece(Color::BLACK, PieceType::QUEEN));  break;
                case 'k': board[i][boardIndex] = Square(Piece(Color::BLACK, PieceType::KING));   break;
                default:
                    std::stringstream errorMessage;
                    errorMessage << "Unexpected symbol in FEN string: " << ranks[i][stringIndex];
                    throw std::invalid_argument{errorMessage.str()};
                    break;
                }
                ++boardIndex;
            }
        }
    }
}