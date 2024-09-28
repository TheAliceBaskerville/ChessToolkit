#ifndef CLICKHANDLER_H
#define CLICKHANDLER_H

#include <SFML/Graphics.hpp>
#include "ClassicChessCanvas.h"
#include "ClassicChessDrawer.h"
#include "ClickAction.h"

class ClickHandler {
    private:
        bool figureIsSelected;
        int selectedRank;
        int selectedFile;
        ClickAction clickAction;
        bool isPiece(int rank, int file, std::vector<std::vector<std::string>>& board) const;
        bool isCurrentColor(int rank, int file, std::vector<std::vector<std::string>>& board) const;
        ClickHandler& analyzeMouseInputFromBoard(ClassicChessCanvas& canvas, sf::Event* event);
        ClickHandler& checkClickLeftButtonFromBoard(int cordx, int cordy, ClassicChessCanvas& canvas);
        ClickHandler& checkClickRightButtonFromBoard();
    public:
        ClickHandler(sf::RenderWindow* window, ClassicChessCanvas& drawingCanvas);
        ~ClickHandler();
        ClickHandler& analyzeMouseInput(ClassicChessCanvas& canvas, sf::Event* event);
};

#endif
