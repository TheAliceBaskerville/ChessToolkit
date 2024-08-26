#ifndef DRAVINGCANVAS_H
#define DRAVINGCANVAS_H

#include <SFML/Graphics.hpp>
#include <piecesImages.h>

class DrawingCanvas {
    private:
        //сделать глобальной
        int width = 512;
        int height = 512;
        
        int dimensionX;
        int dimensionY;
        int squareSize;
        int focusCordX;
        int focusCordY;
        PiecesImages piecesImages;
    public:
        DrawingCanvas();
        ~DrawingCanvas();
        DrawingCanvas& drawEmptyBoard(sf::RenderWindow* window);
        DrawingCanvas& drawPieces(sf::RenderWindow* window);
        DrawingCanvas& drawFocus(sf::RenderWindow* window);
        DrawingCanvas& SetFocusCord(int x, int y);
        std::pair<int, int> getRankAndFileFromCords(int x, int y);
        DrawingCanvas& removeFocus();
        DrawingCanvas& resize();
};

#endif