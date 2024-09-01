#ifndef CLICKHANDLER_H
#define CLICKHANDLER_H

#include <SFML/Graphics.hpp>
#include <DrawingCanvas.h>
#include <ClickAction.h>

class ClickHandler {
    private:
        bool figureIsSelected;
        int selectedRank;
        int selectedFile;
        ClickAction clickAction;
        bool isPiece(int rank, int file, std::vector<std::vector<std::string>>& board);
        bool isCurrentColor(int rank, int file, std::vector<std::vector<std::string>>& board);
        ClickHandler& analyzeMouseInputFromBoard(DrawingCanvas* canvas, sf::Event* event);
        ClickHandler& checkClickLeftButtonFromBoard(int cordx, int cordy, DrawingCanvas* canvas);
        ClickHandler& checkClickRightButtonFromBoard();
    public:
        ClickHandler(sf::RenderWindow* window, DrawingCanvas* drawingCanvas);
        ~ClickHandler();
        ClickHandler& analyzeMouseInput(DrawingCanvas* canvas, sf::Event* event);
};

#endif
