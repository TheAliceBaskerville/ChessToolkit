#ifndef DRAVINGCANVAS_H
#define DRAVINGCANVAS_H

#include <SFML/Graphics.hpp>
#include <piecesImages.h>

class DrawingCanvas {
    private:
        int dimensionX;
        int dimensionY;
        int squareSize;
        int focusCordX;
        int focusCordY;
        PiecesImages piecesImages;
        int calculateSquareSize(int wigth, int height);
    public:
        DrawingCanvas(int width, int height);
        ~DrawingCanvas();
        DrawingCanvas& drawEmptyBoard(sf::RenderWindow* window);
        DrawingCanvas& drawPieces(sf::RenderWindow* window);
        DrawingCanvas& drawFocus(sf::RenderWindow* window);
        std::pair<int, int> getRankAndFileFromCords(int x, int y);
        DrawingCanvas& removeFocus();
        DrawingCanvas& resize(int width, int height);

        DrawingCanvas& SetFocusCord(int x, int y);
        int getSquareSize();
        std::pair<int, int> getDimesions();
};

#endif