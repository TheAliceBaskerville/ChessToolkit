#include <SFML/Graphics.hpp>
#include <drawingCanvas.h>
#include <ClickHandler.h>
#include <KeyboardHandler.h>

int main()
{
    sf::RenderWindow window = sf::RenderWindow{ { 512u, 512u }, "ChessToolKit" };
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);
    DrawingCanvas canvas;
    ClickHandler clickHandler{&window, &canvas};
    KeyboardHandler keyboardHandler{&window, &canvas};

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                clickHandler.analyzeMouseInputFromBoard(event.mouseButton.x, event.mouseButton.y, &canvas, &event);
            }
            if(event.type == sf::Event::KeyPressed) {
                keyboardHandler.analyzeKeyboardInput(&event);
            }
        }
        window.clear(sf::Color::White);
        canvas.drawEmptyBoard(&window);
        canvas.drawFocus(&window);
        canvas.drawPieces(&window);
        window.display();
    }
}
