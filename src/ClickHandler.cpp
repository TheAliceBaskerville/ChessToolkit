#include "ClickHandler.h"

ClickHandler::ClickHandler(sf::RenderWindow* window, ClassicChessCanvas& drawingCanvas)
: clickAction(drawingCanvas, window) {
    figureIsSelected = false;
    selectedRank = -1;
    selectedFile = -1;
}

ClickHandler::~ClickHandler() {}

ClickHandler& ClickHandler::analyzeMouseInput(ClassicChessCanvas& canvas, sf::Event* event) {
    int squareSize = canvas.getSquareSize();
    std::pair<int, int> dimansions = canvas.getDimensions();

    if((event->mouseButton.x > (dimansions.first * squareSize)) || (event->mouseButton.y > (dimansions.second * squareSize))) {
        return *this;
    }else {
        return analyzeMouseInputFromBoard(canvas, event);
    }
}

ClickHandler& ClickHandler::analyzeMouseInputFromBoard(ClassicChessCanvas& canvas, sf::Event* event) {
    switch (event->mouseButton.button)
    {
    case sf::Mouse::Left:
        checkClickLeftButtonFromBoard(event->mouseButton.x, event->mouseButton.y, canvas);
        break;
    case sf::Mouse::Right:
        checkClickRightButtonFromBoard();
        break;
    default:
        break;
    }
    return *this;
}

ClickHandler& ClickHandler::checkClickLeftButtonFromBoard(int x, int y, ClassicChessCanvas& canvas) {

    std::pair<int, int> rankAndFile{ClassicChess::getRankAndFileFromCords(x, y, canvas)};

    std::vector<std::vector<std::string>> board{ { "bR", "wR", "--", "--", "--", "--", "--", "bQ" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" }, 
                                                     { "--", "bR", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" }, 
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },   
                                                     { "--", "--", "--", "bR", "--", "--", "--", "--" } };

    if(figureIsSelected) {
        if ((rankAndFile.first == selectedRank) && (rankAndFile.second == selectedFile)) {
            clickAction.removeFocus();
            figureIsSelected = false;
            selectedRank = -1;
            selectedFile = -1;
            return *this;
        }
        if(isPiece(rankAndFile.first, rankAndFile.second, board) && isCurrentColor(rankAndFile.first, rankAndFile.second, board)) {
            selectedRank = rankAndFile.first;
            selectedFile = rankAndFile.second;
            clickAction.setFocus(selectedRank, selectedFile);
            figureIsSelected = true;
        }else {
            clickAction.createMove(selectedRank, selectedFile, rankAndFile.first, rankAndFile.second);
            clickAction.removeFocus();
            figureIsSelected = false;
            selectedRank = -1;
            selectedFile = -1;
        }
    }else {
        if(isPiece(rankAndFile.first, rankAndFile.second, board) && isCurrentColor(rankAndFile.first, rankAndFile.second, board)) {
            selectedRank = rankAndFile.first;
            selectedFile = rankAndFile.second;
            clickAction.setFocus(selectedRank, selectedFile);
            figureIsSelected = true;
        }
    }
    return *this;
}

ClickHandler& ClickHandler::checkClickRightButtonFromBoard() {
    return *this;
}

bool ClickHandler::isPiece(int rank, int file, std::vector<std::vector<std::string>>& board) const {
    if(board[static_cast<std::size_t>(file)][static_cast<std::size_t>(rank)] != "--") {
        return true;
    }
    return false;
}

bool ClickHandler::isCurrentColor(int rank, int file, std::vector<std::vector<std::string>>& board) const {
    std::string color = board[static_cast<std::size_t>(file)][static_cast<std::size_t>(rank)].substr(0, 1);
    if(color == "b") {
        return true;
    }
    return false;
}