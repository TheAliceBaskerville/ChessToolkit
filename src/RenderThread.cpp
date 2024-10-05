#include "RenderThread.h"

void RenderThread::renderClassicChessboard(sf::RenderWindow& window, ClassicChessCanvas& canvas, const bool& isRunning) {

    window.setActive();

    while (isRunning) {
        window.clear(sf::Color::White);
        ClassicChessDrawer::drawEmptyBoard(&window, canvas);
        ClassicChessDrawer::drawFocus(&window, canvas);
        ClassicChessDrawer::drawPieces(&window, canvas);
        window.display();
    }
};