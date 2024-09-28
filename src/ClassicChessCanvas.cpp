#include "ClassicChessCanvas.h"


//        .==.        .==.          
//       //`^\\      //^`\\         
//      // ^ ^\(\__/)/^ ^^\\        
//     //^ ^^ ^/6  6\ ^^ ^ \\       
//    //^ ^^ ^/( .. )\^ ^ ^ \\      
//   // ^^ ^/\| v""v |/\^ ^ ^\\     
//  // ^^/\/ /  `~~`  \ \/\^ ^\\    
//  -----------------------------

ClassicChessCanvas::ClassicChessCanvas(int width, int height) {
    dimensionX = 8;
    dimensionY = 8;
    int widthSquareSize = width / dimensionX;
    int heightSquareSize = height / dimensionY;
    if (widthSquareSize < heightSquareSize) {
        squareSize = widthSquareSize;
    } else {
        squareSize = heightSquareSize;
    }
    focusCordX = -1;
    focusCordY = -1;
}

ClassicChessCanvas::~ClassicChessCanvas(){}

int ClassicChessCanvas::getDimensionX() const {
    std::lock_guard<std::mutex> lock(mutex);
    return dimensionX;
}

int ClassicChessCanvas::getDimensionY() const {
    std::lock_guard<std::mutex> lock(mutex);
    return dimensionY;
}

std::pair<int, int> ClassicChessCanvas::getFocusCordPair() const {
    std::lock_guard<std::mutex> lock(mutex);
    return std::make_pair(focusCordX, focusCordY);
}

int ClassicChessCanvas::getFocusCordX() const {
    std::lock_guard<std::mutex> lock(mutex);
    return focusCordX;
}

std::pair<int, int> ClassicChessCanvas::getDimensions() const {
    std::lock_guard<std::mutex> lock(mutex);
    return std::make_pair(dimensionX, dimensionY);
}

int ClassicChessCanvas::getFocusCordY() const {
    std::lock_guard<std::mutex> lock(mutex);
    return focusCordY;
}

int ClassicChessCanvas::getSquareSize() const {
    std::lock_guard<std::mutex> lock(mutex);
    return squareSize;
}

std::map<std::string, sf::Image> ClassicChessCanvas::getPiecesImages() const {
    std::lock_guard<std::mutex> lock(mutex);
    return piecesImages.GetPiecesImages();
}

void ClassicChessCanvas::setDimensionX(int dimensionX) {
    std::lock_guard<std::mutex> lock(mutex);
    this->dimensionX = dimensionX;
}
void ClassicChessCanvas::setDimensionY(int dimensionY) {
    std::lock_guard<std::mutex> lock(mutex);
    this->dimensionY = dimensionY;
}
void ClassicChessCanvas::setFocusCordX(int focusCordX) {
    std::lock_guard<std::mutex> lock(mutex);
    this->focusCordX = focusCordX;
}
void ClassicChessCanvas::setFocusCordY(int focusCordY) {
    std::lock_guard<std::mutex> lock(mutex);
    this->focusCordY = focusCordY;
}
void ClassicChessCanvas::setSquareSize(int squareSize) {
    std::lock_guard<std::mutex> lock(mutex);
    this->squareSize = squareSize;
}