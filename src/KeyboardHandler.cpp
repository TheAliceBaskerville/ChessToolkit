#include <KeyboardHandler.h>

KeyboardHandler::KeyboardHandler(sf::RenderWindow* window, ClassicChessCanvas& drawingCanvas) 
: keyboardAction(window, drawingCanvas) {

}

KeyboardHandler::~KeyboardHandler() {
}

KeyboardHandler& KeyboardHandler::analyzeKeyboardInput(sf::Event* event) {
    switch (event->key.code)
    {
    case sf::Keyboard::Key::Z:
        undo();
        break;
    case sf::Keyboard::Key::X:
        redo();
        break;
    case sf::Keyboard::Key::C:
        switchNotationMode();
        break;
    default:
        break;
    }
    return *this;
}

KeyboardHandler& KeyboardHandler::undo() {
    keyboardAction.undo();
    return *this;
}

KeyboardHandler& KeyboardHandler::redo() {
    keyboardAction.redo();
    return *this;
}

KeyboardHandler& KeyboardHandler::switchNotationMode() {
    keyboardAction.switchNotationMode();
    return *this;
}