#ifndef CLICKACTION_H
#define CLICKACTION_H

#include <SFML/Graphics.hpp>
#include <DrawingCanvas.h>

class ClickAction
{
private:
    DrawingCanvas* canvas;
    sf::RenderWindow* window;
public:
    ClickAction(DrawingCanvas* canvas, sf::RenderWindow* window);
    ClickAction();
    ~ClickAction();
    ClickAction& setFocus(int x, int y);
    ClickAction& createMove(int startRank, int startFile, int endRank, int endFile);
    ClickAction& removeFocus();
};

#endif
