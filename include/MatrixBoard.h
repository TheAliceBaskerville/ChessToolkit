#ifndef MATRIXBOARD_H
#define MATRIXBOARD_H

#include <vector>
#include "IChessBoard.h"
#include "FEN.h"

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
    // notationToIndex responsible for checking if given file and rank are valid.
    std::pair<int, int> notationToIndex(int file, int rank) const;
    std::pair<int, int> notationToIndex(const std::pair<int, int>& notation) const;
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

    bool isExist(int file, int rank) const override;
    bool isExist(std::pair<int, int> position) const override;
    bool isEmpty(int file, int rank) const override;
    bool isEmpty(std::pair<int, int> position) const override;
    std::optional<Piece> getAt(int file, int rank) const override;
    std::optional<Piece> getAt(std::pair<int, int> position) const override;

    MatrixBoard& setAt(int file, int rank, const Piece& piece) override;
    MatrixBoard& setAt(std::pair<int, int> position, const Piece& piece) override;
    MatrixBoard& clearAt(int file, int rank) override;
    MatrixBoard& clearAt(std::pair<int, int> position) override;
    MatrixBoard& removeAt(int file, int rank) override;
    MatrixBoard& removeAt(std::pair<int, int> position) override;
    MatrixBoard& clear() override;

    MatrixBoard& fromFEN(const FEN& FEN) override;
};

#endif