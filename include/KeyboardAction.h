#ifndef KEYBOARDACTION_H
#define KEYBOARDACTION_H

#include <SFML/Graphics.hpp>
#include "ClassicChessCanvas.h"
#include "ClassicChessDrawer.h"

class KeyboardAction
{
private:
    ClassicChessCanvas& canvas;
    sf::RenderWindow* window;
public:
    KeyboardAction(sf::RenderWindow* window, ClassicChessCanvas& drawingCanvas);
    ~KeyboardAction();
    KeyboardAction& undo();
    KeyboardAction& redo();
    KeyboardAction& switchNotationMode();
};

#endif
