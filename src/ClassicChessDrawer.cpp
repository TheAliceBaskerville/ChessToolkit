#include "ClassicChessDrawer.h"

void ClassicChessDrawer::drawEmptyBoard(sf::RenderWindow& window, const ClassicChessCanvas& canvas) {
    std::size_t dimensionX = static_cast<std::size_t>(canvas.getDimensionX());
    std::size_t dimensionY = static_cast<std::size_t>(canvas.getDimensionY());
    std::size_t squareSize = static_cast<std::size_t>(canvas.getSquareSize());
    for(std::size_t rank{0}; rank < dimensionX; ++rank) {
        for(std::size_t file{0}; file < dimensionY; ++file) {
            sf::RectangleShape square;
            square.setSize(sf::Vector2f(static_cast<float>(squareSize), static_cast<float>(squareSize)));

            if((rank + file) % 2 == 0) {
                square.setFillColor(sf::Color(255, 255, 255));
            }else {
                square.setFillColor(sf::Color(0, 0, 0));
            }

            square.setPosition(sf::Vector2f(rank * squareSize, file * squareSize));
            window.draw(square);
        }
    }
}

namespace {
    const int calculateSquareSize(int width, int height, const ClassicChessCanvas& canvas) {
        int widthSquareSize, heightSquareSize;
        widthSquareSize = width / canvas.getDimensionX();
        heightSquareSize = height / canvas.getDimensionY();
        if (widthSquareSize < heightSquareSize) {
            return widthSquareSize;
        } 
        else {
            return heightSquareSize;
        }
    }

    void drawNotationWhite(sf::RenderWindow& window, const ClassicChessCanvas& canvas, sf::Text text, int fontSize) {

        std::size_t fileCount{static_cast<std::size_t>(canvas.getDimensionY())};
        std::size_t rankCount{static_cast<std::size_t>(canvas.getDimensionX())};
        std::size_t squareSize{static_cast<std::size_t>(canvas.getSquareSize())};

        for(std::size_t file{0}; file < fileCount; ++file) {
            text.setString(std::to_string(fileCount - file));
            text.setPosition(0, squareSize * file);
            window.draw(text);
        }

        for(std::size_t rank{0}; rank < rankCount; ++rank) {
            text.setString(fileToChar(rank));
            text.setPosition(((rank + 1) * squareSize) - static_cast<std::size_t>(fontSize), (fileCount * squareSize) - static_cast<std::size_t>(fontSize * 1.25));
            window.draw(text);
        }
    }

    void drawNotationBlack(sf::RenderWindow& window, const ClassicChessCanvas& canvas, sf::Text text, int fontSize) {
        
        std::size_t fileCount{static_cast<std::size_t>(canvas.getDimensionY())};
        std::size_t rankCount{static_cast<std::size_t>(canvas.getDimensionX())};
        std::size_t squareSize{static_cast<std::size_t>(canvas.getSquareSize())};

        for(std::size_t file{0}; file < fileCount; ++file) {
            text.setString(std::to_string(file + 1));
            text.setPosition(0, squareSize * file);
            window.draw(text);
        }

        for(std::size_t rank{0}; rank < rankCount; ++rank) {
            text.setString(fileToChar(rankCount - (rank +  1)));
            text.setPosition(((rank + 1) * squareSize) - static_cast<std::size_t>(fontSize), (fileCount * squareSize) - static_cast<std::size_t>(fontSize * 1.25));
            window.draw(text);
        }
    }
}
void ClassicChessDrawer::resize(int width, int height, ClassicChessCanvas& canvas) {
    canvas.setSquareSize(calculateSquareSize(width, height, canvas));
}

void ClassicChessDrawer::drawFocus(sf::RenderWindow& window, const ClassicChessCanvas& canvas) {
    std::size_t focusCordX = static_cast<std::size_t>(canvas.getFocusCordX());
    std::size_t focusCordY = static_cast<std::size_t>(canvas.getFocusCordY());
    std::size_t squareSize = static_cast<std::size_t>(canvas.getSquareSize());

    if((static_cast<int>(focusCordX) != -1) && (static_cast<int>(focusCordY) != -1)) {
        std::size_t thickness = 5;
        std::pair<std::size_t, std::size_t> rankAndFile{focusCordX, focusCordY};
        sf::RectangleShape square;
        square.setSize(sf::Vector2f{static_cast<float>(squareSize - thickness * 2), static_cast<float>(squareSize - thickness * 2)});
        square.setOutlineThickness(thickness);
        square.setOutlineColor(sf::Color{0, 0, 255});
        square.setFillColor(sf::Color{0,0,0,0});
        square.setPosition(sf::Vector2f{static_cast<float>((rankAndFile.first * squareSize) + thickness), static_cast<float>((rankAndFile.second * squareSize) + thickness)});
        window.draw(square);
    }
}

void ClassicChessDrawer::drawPieces(sf::RenderWindow& window, const ClassicChessCanvas& canvas) {
    //
     std::vector<std::vector<std::string>> board{ { "bR", "wR", "--", "--", "--", "--", "--", "bQ" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" }, 
                                                     { "--", "bR", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" }, 
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },   
                                                     { "--", "--", "--", "bR", "--", "--", "--", "--" } };
    //

    //
     std::vector<std::vector<std::string>> board1{ { "bR", "--", "--", "--", "--", "--", "--", "bQ" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" }, 
                                                     { "--", "bR", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "bR", "--", "--", "--", "--" }, 
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },
                                                     { "--", "--", "--", "--", "--", "--", "--", "--" },   
                                                     { "--", "--", "--", "bR", "--", "--", "--", "--" } };
    //
    static int flag = 0;
    for(std::size_t rank{0}; rank < static_cast<std::size_t>(canvas.getDimensionX()); ++rank) {
        for(std::size_t file{0}; file < static_cast<std::size_t>(canvas.getDimensionY()); ++file) {
            std::string piece;
            if((flag / 10) % 2 == 0) {
                piece = board[file][rank];
            }else {
                piece = board1[file][rank];
            }
            // std::string piece = board[file][rank];
            if(piece != "--") {
                sf::Texture pieceTexture;
                pieceTexture.loadFromImage(canvas.getPiecesImages()[piece]);
                sf::Sprite pieceSprite;
                pieceSprite.setScale(static_cast<float>(canvas.getSquareSize()) / 64, static_cast<float>(canvas.getSquareSize()) / 64);
                pieceSprite.setTexture(pieceTexture);
                pieceSprite.setPosition(rank * static_cast<std::size_t>(canvas.getSquareSize()), file * static_cast<std::size_t>(canvas.getSquareSize()));
                window.draw(pieceSprite);
            }
        }
    }
    ++flag;
}

const std::pair<int, int> ClassicChessDrawer::getRankAndFileFromCords(int cordX, int cordY, const ClassicChessCanvas& canvas) {
    int squareSize = canvas.getSquareSize();
    return std::make_pair(cordX / squareSize, cordY / squareSize);
}

void ClassicChessDrawer::removeFokus(ClassicChessCanvas& canvas) {
    canvas.setFocusCordX(-1);
    canvas.setFocusCordY(-1);
}

sf::Font font;
bool showNotation{true};

void ClassicChessDrawer::switchNotationMode() {
    if(showNotation) {
        showNotation = false;
    } else {
        showNotation = true;
    }
}

void ClassicChessDrawer::drawNotation(sf::RenderWindow& window, const ClassicChessCanvas& canvas) {
    if(!showNotation) {
        return;
    }
    //шрифт должен храниться в файле настроек и быть одним на всю программу
    if (!font.loadFromFile("../fonts/impact2.ttf")) {
        return;
    }
    int fontSize{20};
    sf::Text text("", font, static_cast<unsigned int>(fontSize));
    text.setFillColor(sf::Color::Green);

    //получаю от движка
    bool white{true};

    if(white) {
        drawNotationWhite(window, canvas, text, fontSize);
    } else {
        drawNotationBlack(window, canvas, text, fontSize);
    }
}

//подумать над переносом в класс
void ClassicChessDrawer::SetFocusCord(int x, int y, ClassicChessCanvas& canvas) {
    if ((x >= 0) && (y >= 0)) {
        canvas.setFocusCordX(x);
        canvas.setFocusCordY(y);
    }
}

