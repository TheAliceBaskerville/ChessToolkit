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
    public:
        ClickHandler(sf::RenderWindow* window, DrawingCanvas* drawingCanvas);
        ClickHandler();
        ~ClickHandler();
        ClickHandler& checkClickLeftButton(int cordx, int cordy, DrawingCanvas* canvas);
        ClickHandler& checkClickRightButton();
};

#endif
