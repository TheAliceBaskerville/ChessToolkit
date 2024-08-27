#include "ClickHandler.h"

ClickHandler::ClickHandler(sf::RenderWindow* window, DrawingCanvas* drawingCanvas)
: clickAction(drawingCanvas, window) {
    figureIsSelected = false;
    selectedRank = -1;
    selectedFile = -1;
}

ClickHandler::~ClickHandler() {}

ClickHandler& ClickHandler::analyzeMouseInputFromBoard(int cordx, int cordy, DrawingCanvas* canvas, sf::Event* event) {
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

ClickHandler& ClickHandler::checkClickLeftButtonFromBoard(int x, int y, DrawingCanvas* canvas) {

    std::pair<int, int> rankAndFile{canvas->getRankAndFileFromCords(x, y)};

    std::vector<std::vector<std::string>> board{ { "bR", "wR", "--", "--", "--", "--", "--", "bQ" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" }, 
                                                     { "--", "bR", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" }, 
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },   
                                                     { "--", "--", "--", "bR", "--", "--", "--", "--" } };

    if(figureIsSelected) {
        if(isPiece(rankAndFile.first, rankAndFile.second, board) && isCurrentColor(rankAndFile.first, rankAndFile.second, board)) {
            selectedRank = rankAndFile.first;
            selectedFile = rankAndFile.second;
            clickAction.setFocus(rankAndFile.first, rankAndFile.second);
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
            clickAction.setFocus(rankAndFile.first, rankAndFile.second);
            figureIsSelected = true;
        }
    }
    
    return *this;
}

ClickHandler& ClickHandler::checkClickRightButtonFromBoard() {
    // if(figureIsSelected) {
    //     std::cout << "321";
    //     figureIsSelected = false;
    //     selectedRank = -1;
    //     selectedFile = -1;
    //     clickAction.removeFocus();
    // }
    return *this;
}

bool ClickHandler::isPiece(int rank, int file, std::vector<std::vector<std::string>>& board) {
    if(board[file][rank] != "--") {
        return true;
    }
    return false;
}

bool ClickHandler::isCurrentColor(int rank, int file, std::vector<std::vector<std::string>>& board) {
    std::string color = board[file][rank].substr(0, 1);
    if(color == "b") {
        return true;
    }
    return false;
}