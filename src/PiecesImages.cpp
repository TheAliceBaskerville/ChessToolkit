#include "PiecesImages.h"

PiecesImages::PiecesImages() {
    std::vector<std::string> pieces{"bR", "bN", "bB", "bQ", "bK", "bp", "wR", "wN", "wB", "wQ", "wK", "wp"};
    for(int i{0}; i < pieces.size(); ++i) {
        std::string color{pieces[i].substr(0, 1)};
        sf::Image im;
        if(color == "w") {
            im.loadFromFile("D:\\projects\\ChessToolkit\\resources\\images\\white\\" + pieces[i] + ".png");
        }else {
            im.loadFromFile("D:\\projects\\ChessToolkit\\resources\\images\\black\\" + pieces[i] + ".png");
        }
        piecesImages[pieces[i]] = im;
    }
}

PiecesImages::PiecesImages(std::vector<std::string> pieces) {
    for(int i{0}; i < pieces.size(); ++i) {
        std::string color = pieces[i].substr(0, 1);
        sf::Image im;
        if(color == "w") {
            im.loadFromFile("D:\\projects\\ChessToolkit\\resources\\images\\white\\" + pieces[i] + ".png");
        }else {
            im.loadFromFile("D:\\projects\\ChessToolkit\\resources\\images\\black\\" + pieces[i] + ".png");
        }
        piecesImages[pieces[i]] = im;
    }
}

PiecesImages::~PiecesImages() {
   
}

std::map<std::string, sf::Image> PiecesImages::GetPiecesImages() const {
    return piecesImages;
}