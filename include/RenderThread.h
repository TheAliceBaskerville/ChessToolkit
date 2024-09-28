#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <SFML/Graphics.hpp>
#include "ClassicChessCanvas.h"
#include "ClassicChessDrawer.h"

class RenderThread {
    public:
        static void renderClassicChessboard(sf::RenderWindow& window, ClassicChessCanvas& canvas, const bool& isRunning);
};

#endif

