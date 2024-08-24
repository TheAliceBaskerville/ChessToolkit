#include <SFML/Graphics.hpp>
#include <drawingCanvas.h>

int main()
{
    sf::RenderWindow window = sf::RenderWindow{ { 512u, 512u }, "ChessToolKit" };
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);
    DrawingCanvas canvas;

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
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    canvas.removeFocus();
                    canvas.SetFocusCord(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }
        window.clear(sf::Color::White);
        canvas.drawEmptyBoard(&window);
        canvas.drawFocus(&window);
        canvas.drawPieces(&window);
        window.display();
    }
}
