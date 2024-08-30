#include "DrawingCanvas.h"
#include <iostream>

DrawingCanvas::DrawingCanvas(int width, int height) {
    dimensionX = 8;
    dimensionY = 8;
    squareSize = calculateSquareSize(width, height);
    focusCordX = -1;
    focusCordY = -1;
}

DrawingCanvas::~DrawingCanvas() {
    delete this;
}

DrawingCanvas& DrawingCanvas::resize(int width, int height) {
    squareSize = calculateSquareSize(width, height);
    return *this;
}

int DrawingCanvas::calculateSquareSize(int width, int height) {
    int widthSquareSize, heightSquareSize;
    widthSquareSize = width / dimensionX;
    heightSquareSize = height / dimensionY;
    if (widthSquareSize < heightSquareSize) {
        return widthSquareSize;
    } else {
        return heightSquareSize;
    }
}

std::pair<int,int> DrawingCanvas::getRankAndFileFromCords(int cordX, int cordY) {
    return std::make_pair(cordX / squareSize, cordY / squareSize);
}

DrawingCanvas& DrawingCanvas::drawEmptyBoard(sf::RenderWindow* window) {
    for(int rank{0}; rank < dimensionX; ++rank) {
        for(int file{0}; file < dimensionY; ++file) {
            sf::RectangleShape square;
            square.setSize(sf::Vector2f(squareSize, squareSize));
            square.setOutlineColor(sf::Color::Black);
            square.setOutlineThickness(2);

            if((rank + file) % 2 == 0) {
                square.setFillColor(sf::Color(255, 255, 255));
            }else {
                square.setFillColor(sf::Color(0, 0, 0));
            }

            square.setPosition(sf::Vector2f(rank * squareSize, file * squareSize));
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
    for(int rank{0}; rank < dimensionX; ++rank) {
        for(int file{0}; file < dimensionY; ++file) {
            std::string piece = board[file][rank];
            if(piece != "--") {
                sf::Texture pieceTexture;
                pieceTexture.loadFromImage(piecesImages.GetPiecesImages()[piece]);
                sf::Sprite pieceSprite;
                pieceSprite.setScale(static_cast<float>(squareSize) / 64, static_cast<float>(squareSize) / 64);
                pieceSprite.setTexture(pieceTexture);
                pieceSprite.setPosition(rank * squareSize, file * squareSize);
                window->draw(pieceSprite);
            }
        }
    }
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

int DrawingCanvas::getSquareSize() {
    return squareSize;
}

std::pair<int, int> DrawingCanvas::getDimesions() {
    return std::make_pair(dimensionX, dimensionY);
}