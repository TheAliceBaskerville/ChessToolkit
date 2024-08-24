#include "DrawingCanvas.h"
#include <iostream>

DrawingCanvas::DrawingCanvas() {
    this->width = 512;
    this->height = 512;
    this->dimensionX = 8;
    this->dimensionY = 8;
    this->squareSize = this->height / this->dimensionY;
    this->focusCordX = -1;
    this->focusCordY = -1;
}

DrawingCanvas::~DrawingCanvas() {
    delete this;
}

std::pair<int,int> DrawingCanvas::getRankAndFileForCords(int x, int y) {
    for(int squareRankCordX{0}; squareRankCordX < dimensionX * squareSize; squareRankCordX = squareRankCordX + squareSize) {
        for(int squareRankCordY{0}; squareRankCordY < dimensionY * squareSize; squareRankCordY = squareRankCordY + squareSize) {
            if((x >= squareRankCordX) && (x <= squareRankCordX + squareSize) 
            && (y >= squareRankCordY) && (y <= squareRankCordY + squareSize)) {
                return std::make_pair(squareRankCordX / (dimensionX * dimensionX), squareRankCordY / (dimensionY * dimensionY));
            }
        }
    }
} 

DrawingCanvas& DrawingCanvas::drawEmptyBoard(sf::RenderWindow* window) {
    for(int rank{0}; rank < dimensionX; ++rank) {
        for(int file{0}; file < dimensionY; ++file) {
            
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
     std::vector<std::vector<std::string>> board{ { "bR", "--", "--", "--", "--", "--", "--", "bQ" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" }, 
                                                     { "--", "bR", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" }, 
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },   
                                                     { "--", "--", "--", "bR", "--", "--", "--", "--" } };
    //
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
    return *this;
}

DrawingCanvas& DrawingCanvas::drawFocus(sf::RenderWindow* window) {
    if((focusCordX != -1) && (focusCordY != -1)) {
        std::pair<int, int> rankAndFile = getRankAndFileForCords(focusCordX, focusCordY);
        sf::RectangleShape square;
        square.setSize(sf::Vector2f(squareSize, squareSize));
        square.setOutlineColor(sf::Color::Black);
        square.setOutlineThickness(5);
        square.setOutlineColor(sf::Color(0, 0, 255));

        if((rankAndFile.first + rankAndFile.second) % 2 == 0) {
            square.setFillColor(sf::Color(255, 255, 255));
        }else {
            square.setFillColor(sf::Color(0, 0, 0));
        }

        square.setPosition(sf::Vector2f(rankAndFile.first * squareSize, rankAndFile.second * squareSize));
        window->draw(square);
    }
    return *this;
}

DrawingCanvas& DrawingCanvas::SetFocusCord(int x, int y) {
    if ((x >= 0) && (y >= 0)) {
        this->focusCordX = x;
        this->focusCordY = y;
    }
    std::pair<int,int> pair = getRankAndFileForCords(focusCordX, focusCordY);
    std::cout << pair.first;
    std::cout << "\n";
    std::cout << pair.second;
    return *this;
}

DrawingCanvas& DrawingCanvas::removeFocus() {
    this->focusCordX = -1;
    this->focusCordY = -1;  
    return *this; 
}