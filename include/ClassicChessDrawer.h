#ifndef CLASSICCHESSDRAWER_H
#define CLASSICCHESSDRAWER_H

#include "ClassicChessCanvas.h"
#include "FileConverter.h"
#include <SFML/Graphics.hpp>

namespace ClassicChessDrawer {
    void drawEmptyBoard(sf::RenderWindow& window, const ClassicChessCanvas& canvas);
    void resize(int width, int height, ClassicChessCanvas& canvas);
    const std::pair<int,int> getRankAndFileFromCords(int cordX, int cordY, ClassicChessCanvas& canvas);
    void drawPieces(sf::RenderWindow& window, const ClassicChessCanvas& canvas);
    void drawFocus(sf::RenderWindow& window, const ClassicChessCanvas& canvas);
    void SetFocusCord(int x, int y, ClassicChessCanvas& canvas);
    void removeFokus(ClassicChessCanvas& canvas);
    void drawNotation(sf::RenderWindow& window, const ClassicChessCanvas& canvas);
    void switchNotationMode();
}

#endif