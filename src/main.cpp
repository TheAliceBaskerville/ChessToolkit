#include <SFML/Graphics.hpp>
#include <drawingCanvas.h>
#include <ClickHandler.h>

int main()
{
    sf::RenderWindow window = sf::RenderWindow{ { 512u, 512u }, "ChessToolKit" };
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);
    DrawingCanvas canvas;
    ClickHandler clickHandler{&window, &canvas};

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
                    //создать обёртку
                    clickHandler.checkClickLeftButton(event.mouseButton.x, event.mouseButton.y, &canvas);
                }
                 if (event.mouseButton.button == sf::Mouse::Right) {
                    std::cout << "right";
                    clickHandler.checkClickRightButton();   
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
