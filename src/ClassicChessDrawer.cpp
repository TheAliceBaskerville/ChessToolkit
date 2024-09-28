#include "ClassicChessDrawer.h"

void ClassicChess::drawEmptyBoard(sf::RenderWindow* window, ClassicChessCanvas& canvas) {
    int dimensionX = canvas.getDimensionX();
    int dimensionY = canvas.getDimensionY();
    int squareSize = canvas.getSquareSize();
    for(int rank{0}; rank < dimensionX; ++rank) {
        for(int file{0}; file < dimensionY; ++file) {
            sf::RectangleShape square;
            square.setSize(sf::Vector2f(squareSize, squareSize));

            if((rank + file) % 2 == 0) {
                square.setFillColor(sf::Color(255, 255, 255));
            }else {
                square.setFillColor(sf::Color(0, 0, 0));
            }

            square.setPosition(sf::Vector2f(rank * squareSize, file * squareSize));
            window->draw(square);
        }
    }
}

namespace {
    const int calculateSquareSize(int width, int height, ClassicChessCanvas& canvas) {
        int widthSquareSize, heightSquareSize;
        widthSquareSize = width / canvas.getDimensionX();
        heightSquareSize = height / canvas.getDimensionY();
        if (widthSquareSize < heightSquareSize) {
            return widthSquareSize;
        } 
        else {
            return heightSquareSize;
        }
    }
}
void ClassicChess::resize(int width, int height, ClassicChessCanvas& canvas) {
    canvas.setSquareSize(calculateSquareSize(width, height, canvas));
}

void ClassicChess::drawFocus(sf::RenderWindow* window, ClassicChessCanvas& canvas) {
    int focusCordX = canvas.getFocusCordX();
    int focusCordY = canvas.getFocusCordY();
    int squareSize = canvas.getSquareSize();
    if((focusCordX != -1) && (focusCordY != -1)) {
        int thickness = 5;
        std::pair<int, int> rankAndFile{focusCordX, focusCordY};
        sf::RectangleShape square;
        square.setSize(sf::Vector2f{squareSize - thickness * 2, squareSize - thickness * 2});
        square.setOutlineThickness(thickness);
        square.setOutlineColor(sf::Color{0, 0, 255});
        square.setFillColor(sf::Color{0,0,0,0});
        square.setPosition(sf::Vector2f{(rankAndFile.first * squareSize) + thickness, (rankAndFile.second * squareSize) + thickness});
        window->draw(square);
    }
}

void ClassicChess::drawPieces(sf::RenderWindow* window, ClassicChessCanvas& canvas) {
    //
     std::vector<std::vector<std::string>> board{ { "bR", "wR", "--", "--", "--", "--", "--", "bQ" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" }, 
                                                     { "--", "bR", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" }, 
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },   
                                                     { "--", "--", "--", "bR", "--", "--", "--", "--" } };
    //

    //
     std::vector<std::vector<std::string>> board1{ { "bR", "--", "--", "--", "--", "--", "--", "bQ" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" }, 
                                                     { "--", "bR", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "bR", "--", "--", "--", "--" }, 
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },   
                                                     { "--", "--", "--", "bR", "--", "--", "--", "--" } };
    //
    static int flag = 0;
    for(int rank{0}; rank < canvas.getDimensionX(); ++rank) {
        for(int file{0}; file < canvas.getDimensionY(); ++file) {
            std::string piece;
            if((flag / 10) % 2 == 0) {
                piece = board[file][rank];
            }else {
                piece = board1[file][rank];
            }
            // std::string piece = board[file][rank];
            if(piece != "--") {
                sf::Texture pieceTexture;
                pieceTexture.loadFromImage(canvas.getPiecesImages()[piece]);
                sf::Sprite pieceSprite;
                pieceSprite.setScale(static_cast<float>(canvas.getSquareSize()) / 64, static_cast<float>(canvas.getSquareSize()) / 64);
                pieceSprite.setTexture(pieceTexture);
                pieceSprite.setPosition(rank * canvas.getSquareSize(), file * canvas.getSquareSize());
                window->draw(pieceSprite);
            }
        }
    }
    ++flag;
}

const std::pair<int, int> ClassicChess::getRankAndFileFromCords(int cordX, int cordY, ClassicChessCanvas& canvas) {
    int squareSize = canvas.getSquareSize();
    return std::make_pair(cordX / squareSize, cordY / squareSize);
}

void ClassicChess::removeFokus(ClassicChessCanvas& canvas) {
    canvas.setFocusCordX(-1);
    canvas.setFocusCordY(-1);
}

//подумать над переносом в класс
void ClassicChess::SetFocusCord(int x, int y, ClassicChessCanvas& canvas) {
    if ((x >= 0) && (y >= 0)) {
        canvas.setFocusCordX(x);
        canvas.setFocusCordY(y);
    }
}

