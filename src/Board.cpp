#include <stdexcept>
#include <sstream>
#include "Board.h"

namespace {
    class Square : public ISquare{
    private:
        std::optional<Piece> piece;
    public:
        Square() = default;
        Square(const Piece& piece) : piece{piece}{}
        Square(const Square&) = default;
        Square(Square&&) noexcept = default;
        ~Square() override = default;

        Square& operator=(const Square&) = default;
        Square& operator=(Square&&) noexcept = default;
        bool operator==(const ISquare& other) const override {
            if (const Square* castedOther = dynamic_cast<const Square*>(&other)) {
                return piece == castedOther->piece;
            }
            return false;
        }

        bool isExist() const override {return true;}
        bool isEmpty() const override {return !piece.has_value();}
        std::optional<Piece> getPiece() const override {return piece;}
        Square& setPiece(const Piece& piece) override {this->piece = piece; return *this;}
        Square& setEmpty() override {piece = std::nullopt; return *this;}
        std::unique_ptr<ISquare> clone() const override {return std::make_unique<Square>(*this);}
    };

    class NoSquare : public ISquare{
    public:
        NoSquare() = default;
        ~NoSquare() override = default;
        NoSquare(const NoSquare&) = default;
        NoSquare(NoSquare&&) noexcept = default;
        NoSquare& operator=(const NoSquare&) = default;
        NoSquare& operator=(NoSquare&&) noexcept = default;
        bool operator==(const ISquare& other) const override {
            return dynamic_cast<const NoSquare*>(&other);
        }
        
        bool isExist() const override {return false;}
        bool isEmpty() const override {return false;}
        std::optional<Piece> getPiece() const override {return std::nullopt;}
        ISquare& setPiece(const Piece&) override {
            throw std::logic_error{"Cannot set a piece on a non-existing square."};
        }
        ISquare& setEmpty() override {
            throw std::logic_error{"Cannot set a piece on a non-existing square."};
        }

        std::unique_ptr<ISquare> clone() const override {return std::make_unique<NoSquare>(*this);}
    };
}

Board::Board(std::size_t height, std::size_t width) : width{width}, height{height}{
    board.resize(height);
    for (std::size_t rank{0}; rank < height; ++rank) {
        board.reserve(width);
        for (std::size_t file{0}; file < width; ++file) {
            board[rank].emplace_back(std::make_unique<Square>());
        }
    }
}

Board::Board(const Board& other) : width{other.width}, height{other.height}{
    board.resize(height);
    for (std::size_t rank{0}; rank < height; ++rank){
        board.reserve(width);
        for (std::size_t file{0}; file < width; ++file){
            board[rank].emplace_back(other.board[rank][file]->clone());
        }
    }
}

Board& Board::operator=(const Board& other){
    if (this == &other){
        return *this;
    }

    width = other.width;
    height = other.height;
    board.resize(height);

    for (std::size_t rank{0}; rank < height; ++rank){
        board[rank].resize(width);
        for (std::size_t file{0}; file < width; ++file){
            board[rank][file] = other.board[rank][file]->clone();
        }
    }
    return *this;
}

bool Board::operator==(const Board& other) const{
    if (width != other.width || height != other.height)
        return false;

    for (std::size_t rank{0}; rank < height; ++rank){
        for (std::size_t file{0}; file < width; ++file){
            if (*board[rank][file] != *other.board[rank][file]){
                return false;
            }
        }
    }
    return true;
}

bool Board::operator!=(const Board& other) const{
    return !(*this == other);
}

std::size_t Board::getWidth() const{
    return width;
}

std::size_t Board::getHeight() const{
    return height;
}

std::pair<std::size_t, std::size_t> Board::getSize() const{
    return {height, width};
}

const Position& Board::boundaryCheck(const Position& position) const{
    if (position.getFile() < 1 || position.getFile() > width){
        std::stringstream errorMessage;
        errorMessage << "File is out of range: " << position.getFile();
        throw std::out_of_range{errorMessage.str()};
    }
    if (position.getRank() < 1 || position.getRank() > height){
        std::stringstream errorMessage;
        errorMessage << "Rank is out of range: " << position.getRank();
        throw std::out_of_range{errorMessage.str()};
    }
    return position;
}

bool Board::isExist(const Position& position) const{
    std::pair<std::size_t, std::size_t> indexes = boundaryCheck(position).toIndex(height);
    return board[indexes.first][indexes.second]->isExist();
}

bool Board::isEmpty(const Position& position) const{
    std::pair<std::size_t, std::size_t> indexes = boundaryCheck(position).toIndex(height);
    return board[indexes.first][indexes.second]->isEmpty();
}

std::optional<Piece> Board::getAt(const Position& position) const{
    std::pair<std::size_t, std::size_t> indexes = boundaryCheck(position).toIndex(height);
    return board[indexes.first][indexes.second]->getPiece();
}

Board& Board::setAt(const Position& position, const Piece& piece){
    std::pair<std::size_t, std::size_t> indexes = boundaryCheck(position).toIndex(height);
    board[indexes.first][indexes.second]->setPiece(piece);
    return *this;
}

Board& Board::clearAt(const Position& position){
    std::pair<std::size_t, std::size_t> indexes = boundaryCheck(position).toIndex(height);
    board[indexes.first][indexes.second]->setEmpty();
    return *this;
}

Board& Board::removeAt(const Position& position){
    std::pair<std::size_t, std::size_t> indexes = boundaryCheck(position).toIndex(height);
    board[indexes.first][indexes.second] = std::make_unique<NoSquare>();
    return *this;
}

Board& Board::restoreAt(const Position& position){
    std::pair<std::size_t, std::size_t> indexes = boundaryCheck(position).toIndex(height);
    board[indexes.first][indexes.second] = std::make_unique<Square>();
    return *this;
}

Board& Board::clear(){
    for (std::size_t rank{0}; rank < height; ++rank){
        for (std::size_t file{0}; file < width; ++file){
            if (board[rank][file]->isExist())
                board[rank][file]->setEmpty();
        }
    }
    return *this;
}