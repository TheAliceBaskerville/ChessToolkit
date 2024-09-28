#ifndef CLICKACTION_H
#define CLICKACTION_H

#include "ClassicChessCanvas.h"
#include "ClassicChessDrawer.h"

class ClickAction
{
private:
    ClassicChessCanvas& canvas;
    sf::RenderWindow* window;
public:
    ClickAction(ClassicChessCanvas& canvas, sf::RenderWindow* window);
    ~ClickAction();
    ClickAction& setFocus(int x, int y);
    ClickAction& createMove(int startRank, int startFile, int endRank, int endFile);
    ClickAction& removeFocus();
};

#endif
