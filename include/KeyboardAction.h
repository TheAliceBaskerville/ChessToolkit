#ifndef KEYBOARDACTION_H
#define KEYBOARDACTION_H

#include <SFML/Graphics.hpp>
#include <DrawingCanvas.h>

class KeyboardAction
{
private:
    DrawingCanvas* canvas;
    sf::RenderWindow* window;
public:
    KeyboardAction(sf::RenderWindow* window, DrawingCanvas* drawingCanvas);
    ~KeyboardAction();
    KeyboardAction& undo();
    KeyboardAction& redo();
};

#endif
