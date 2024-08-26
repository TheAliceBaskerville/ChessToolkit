#include <KeyboardAction.h>

KeyboardAction::KeyboardAction(sf::RenderWindow* window, DrawingCanvas* drawingCanvas) {
    this->canvas = drawingCanvas;
    this->window = window;
}

KeyboardAction::~KeyboardAction() {

}

KeyboardAction& KeyboardAction::undo() {
    std::cout << "undo";
    return *this;
}

KeyboardAction& KeyboardAction::redo() {
    std::cout << "redo";
    return *this;
}