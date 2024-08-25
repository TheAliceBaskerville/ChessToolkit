#include "DrawingCanvas.h"
#include <iostream>

DrawingCanvas::DrawingCanvas() {
    width = 512;
    height = 512;
    dimensionX = 8;
    dimensionY = 8;
    squareSize = height / dimensionY;
    focusCordX = -1;
    focusCordY = -1;
}

DrawingCanvas::~DrawingCanvas() {
    delete this;
}

std::pair<int,int> DrawingCanvas::getRankAndFileForCords(int x, int y) {
    //refactor cordX / squareSize
    for(int RankCordX{0}; RankCordX < dimensionX * squareSize; RankCordX = RankCordX + squareSize) {
        for(int RankCordY{0}; RankCordY < dimensionY * squareSize; RankCordY = RankCordY + squareSize) {
            if((x >= RankCordX) && (x <= RankCordX + squareSize) 
            && (y >= RankCordY) && (y <= RankCordY + squareSize)) {
                return std::make_pair(RankCordX / (dimensionX * dimensionX), RankCordY / (dimensionY * dimensionY));
            }
        }
    }
}

DrawingCanvas& DrawingCanvas::drawEmptyBoard(sf::RenderWindow* window) {
    for(int rank{0}; rank < dimensionX; ++rank) {
        for(int file{0}; file < dimensionY; ++file) {
            //refactor to index notation
            
            sf::RectangleShape square;
            square.setSize(sf::Vector2f(squareSize, squareSize));
            square.setOutlineColor(sf::Color::Black);
            square.setOutlineThickness(2);

            if((rank + file) % 2 == 0) {
                square.setFillColor(sf::Color(0, 0, 0));
            }else {
                square.setFillColor(sf::Color(255, 255, 255));
            }

            square.setPosition(sf::Vector2f(file * squareSize, height - (rank + 1) * squareSize));
            window->draw(square);
        }
    }
    return *this;
}

DrawingCanvas& DrawingCanvas::drawPieces(sf::RenderWindow* window) {
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

    //refactor to index notation
    for(int rank{0}; rank < dimensionX; ++rank) {
        for(int file{0}; file < dimensionY; ++file) {
            std::string piece = board[dimensionX - rank - 1][file];
            if(piece != "--") {
                sf::Texture pieceTexture;
                pieceTexture.loadFromImage(piecesImages.GetPiecesImages()[piece]);
                sf::Sprite pieceSprite;
                pieceSprite.setTexture(pieceTexture);
                pieceSprite.setPosition(file * squareSize, height - (rank + 1) * squareSize);
                window->draw(pieceSprite);
            }
        }
    }
    //
    return *this;
}

DrawingCanvas& DrawingCanvas::drawFocus(sf::RenderWindow* window) {
    if((focusCordX != -1) && (focusCordY != -1)) {
        std::pair<int, int> rankAndFile{focusCordX, focusCordY};
        sf::RectangleShape square;
        square.setSize(sf::Vector2f{squareSize, squareSize});
        square.setOutlineColor(sf::Color::Black);
        square.setOutlineThickness(5);
        square.setOutlineColor(sf::Color{0, 0, 255});

        square.setFillColor(sf::Color{0,0,0,0});

        square.setPosition(sf::Vector2f{rankAndFile.first * squareSize, rankAndFile.second * squareSize});
        window->draw(square);
    }
    return *this;
}

DrawingCanvas& DrawingCanvas::SetFocusCord(int x, int y) {
    if ((x >= 0) && (y >= 0)) {
        focusCordX = x;
        focusCordY = y;
    }
    return *this;
}

DrawingCanvas& DrawingCanvas::removeFocus() {
    focusCordX = -1;
    focusCordY = -1;  
    return *this; 
}