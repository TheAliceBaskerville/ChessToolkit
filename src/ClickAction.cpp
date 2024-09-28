#include "ClickAction.h"

ClickAction::ClickAction(ClassicChessCanvas& canvas, sf::RenderWindow* window) : canvas(canvas) {
    this->window = window;
}

ClickAction::~ClickAction() {}

ClickAction& ClickAction::setFocus(int rank, int file) {
    ClassicChess::SetFocusCord(rank, file, canvas);
    return *this;
}

ClickAction& ClickAction::removeFocus() {
    ClassicChess::removeFokus(canvas);
    return *this;
}

ClickAction& ClickAction::createMove(int startRank, int startFile, int endRank, int endFile) {
    //что-то что создаёт ход исходя из координат фокуса и координат щелчка мыши
    std::cout << "moooooooooooooove";
    return *this;
}