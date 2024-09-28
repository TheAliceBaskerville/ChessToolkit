#include "RenderThread.h"

//во всех классах все методы которые не изменяют обьекты должны помечаться как const

void RenderThread::renderClassicChessboard(sf::RenderWindow& window, ClassicChessCanvas& canvas, const bool& isRunning) {

    window.setActive();

    while (isRunning) {
        window.clear(sf::Color::White);
        ClassicChess::drawEmptyBoard(&window, canvas);
        ClassicChess::drawFocus(&window, canvas);
        ClassicChess::drawPieces(&window, canvas);
        window.display();
    }
    std::cout << "nope";
};