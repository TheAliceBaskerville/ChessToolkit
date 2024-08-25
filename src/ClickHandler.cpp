#include "ClickHandler.h"

ClickHandler::ClickHandler(sf::RenderWindow* window, DrawingCanvas* drawingCanvas) {
    figureIsSelected = false;
    ClickAction clickAction{drawingCanvas, window};
    this->clickAction = clickAction;
}

ClickHandler::ClickHandler() {
    figureIsSelected = false;
}

ClickHandler::~ClickHandler() {}

ClickHandler& ClickHandler::checkClickLeftButton(int x, int y, DrawingCanvas* canvas) {
    //from
    std::pair<int, int> rankAndFile{canvas->getRankAndFileForCords(x, y)};
    //
    std::vector<std::vector<std::string>> board{ { "bR", "wR", "--", "--", "--", "--", "--", "bQ" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" }, 
                                                     { "--", "bR", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" }, 
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },   
                                                     { "--", "--", "--", "bR", "--", "--", "--", "--" } };
    //  for(int i{0}; i < 8; ++i) {
    //         for( int k{0}; k < 8; ++k) {
    //             std::cout << board[rankAndFile.second][rankAndFile.first];
    //         }
    //     std::cout << "\n";
    //     }
    //
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

ClickHandler& ClickHandler::checkClickRightButton() {
    if(figureIsSelected) {
        std::cout << "321";
        figureIsSelected = false;
        selectedRank = -1;
        selectedFile = -1;
        clickAction.removeFocus();
    }
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
        std::cout << "1";
        return true;
    }
    return false;
}