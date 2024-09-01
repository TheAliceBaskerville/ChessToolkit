#ifndef MATRIXBOARD_H
#define MATRIXBOARD_H

#include <memory>
#include <vector>
#include "IChessBoard.h"
#include "FEN.h"

/*
Add boundary check for positions:
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
*/

class MatrixBoard : public IChessBoard{
private:
    class Square{
    private:
        bool isExistFlag, isEmptyFlag;
        Piece piece; // Contains trash if (!isExistFlag || isEmptyFlag)
    public:
        Square(bool isExist=false);
        Square(const Piece& piece);
        ~Square();

        bool isExist() const;
        bool isEmpty() const;
        const Piece& getPiece() const;
        Square& setExist(bool isExistFlag);
        Square& setEmpty(bool isEmptyFlag);
        Square& setPiece(const Piece& piece);

        bool operator==(const Square& other) const;
        bool operator!=(const Square& other) const;
    };
private:
    std::vector<std::vector<Square>> board;
    int width, height;
public:
    MatrixBoard(int height=8, int width=8);
    MatrixBoard(const FEN& FEN);
    MatrixBoard(const MatrixBoard& other);
    MatrixBoard(MatrixBoard&& other) noexcept;
    ~MatrixBoard() override;

    MatrixBoard& operator=(const MatrixBoard& other);
    MatrixBoard& operator=(MatrixBoard&& other) noexcept;

    bool operator==(const MatrixBoard& other) const;
    bool operator!=(const MatrixBoard& other) const;

    int getWidth() const override;
    int getHeight() const override;
    std::pair<int, int> getSize() const override;

    bool isExist(const Position& position) const override;
    bool isEmpty(const Position& position) const override;
    std::optional<Piece> getAt(const Position& position) const override;

    MatrixBoard& setAt(const Position& position, const Piece& piece) override;
    MatrixBoard& clearAt(const Position& position) override;
    MatrixBoard& removeAt(const Position& position) override;
    MatrixBoard& clear() override;

    MatrixBoard& fromFEN(const FEN& FEN) override;

    std::unique_ptr<IChessBoard> clone() const override;
};

#endif