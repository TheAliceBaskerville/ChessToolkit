#ifndef CLASSICCHESSDRAWER_H
#define CLASSICCHESSDRAWER_H

#include "ClassicChessCanvas.h"
#include <SFML/Graphics.hpp>

namespace ClassicChess {
    void drawEmptyBoard(sf::RenderWindow* window, ClassicChessCanvas& canvas);
    void resize(int width, int height, ClassicChessCanvas& canvas);
    const std::pair<int,int> getRankAndFileFromCords(int cordX, int cordY, ClassicChessCanvas& canvas);
    void drawPieces(sf::RenderWindow* window, ClassicChessCanvas& canvas);
    void drawFocus(sf::RenderWindow* window, ClassicChessCanvas& canvas);
    void SetFocusCord(int x, int y, ClassicChessCanvas& canvas);
    void removeFokus(ClassicChessCanvas& canvas);
}

#endif