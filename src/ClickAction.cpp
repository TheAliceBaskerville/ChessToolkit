#include "ClickAction.h"

ClickAction::ClickAction(DrawingCanvas* canvas, sf::RenderWindow* window) {
    this->canvas = canvas;
    this->window = window;
}

ClickAction::~ClickAction() {}

ClickAction& ClickAction::setFocus(int rank, int file) {
    canvas->SetFocusCord(rank, file);
    return *this;
}

ClickAction& ClickAction::removeFocus() {
    canvas->removeFocus();
    return *this;
}

ClickAction& ClickAction::createMove(int startRank, int startFile, int endRank, int endFile) {
    //что-то что создаёт ход исходя из координат фокуса и координат щелчка мыши
    std::cout << "moooooooooooooove";
    return *this;
}