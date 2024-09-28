#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "KeyboardAction.h"
#include "ClassicChessCanvas.h"

class KeyboardHandler
{
private:
    KeyboardAction keyboardAction;
    KeyboardHandler& undo();
    KeyboardHandler& redo();
public:
    KeyboardHandler(sf::RenderWindow* window, ClassicChessCanvas& drawingCanvas);
    ~KeyboardHandler();
    KeyboardHandler& analyzeKeyboardInput(sf::Event* event);
};

#endif
