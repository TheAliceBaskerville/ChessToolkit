#ifndef PIECESIMAGES_H
#define PIECESIMAGES_H

#include <map>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class PiecesImages {
    private:
        std::map<std::string, sf::Image> piecesImages;
    public:
        PiecesImages();
        PiecesImages(std::vector<std::string> pieces);
        ~PiecesImages();
        std::map<std::string, sf::Image> GetPiecesImages() const;
};

#endif