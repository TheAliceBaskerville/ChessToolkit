#ifndef CLASSICCHESSCANVAS_H
#define CLASSICCHESSCANVAS_H

#include <piecesImages.h>
#include <mutex>

class ClassicChessCanvas
{
private:
    mutable std::mutex mutex;
    int dimensionX;
    int dimensionY;
    int squareSize;
    int focusCordX;
    int focusCordY;
    PiecesImages piecesImages;
public:
    ClassicChessCanvas(int width, int height);
    ~ClassicChessCanvas();
    int getDimensionX() const;
    int getDimensionY() const;
    int getSquareSize() const;
    int getFocusCordX() const;
    int getFocusCordY() const;
    std::map<std::string, sf::Image> getPiecesImages() const;
    std::pair<int, int> getDimensions() const;
    std::pair<int, int> getFocusCordPair() const;
    void setDimensionX(int dimensionX);
    void setDimensionY(int dimensionY);
    void setSquareSize(int squareSize);
    void setFocusCordX(int focusCordX);
    void setFocusCordY(int focusCordY);
};

#endif