#include <SFML/Graphics.hpp>
#include <drawingCanvas.h>
#include <ClickHandler.h>
#include <KeyboardHandler.h>

void resize(int width, int height, sf::RenderWindow* window, DrawingCanvas* canvas) {
    //при свайпе в право почему-то двигает окно, а не возвращает в исходное состояние
    window->setSize(sf::Vector2u(static_cast<unsigned int>(width), static_cast<unsigned int>(height)));
    sf::FloatRect visibleArea(0, 0, width, height);
    window->setView(sf::View(visibleArea));
    canvas->resize(width, height);
}

int main()
{
    int width = 512u;
    int height = 512u;
    sf::RenderWindow window = sf::RenderWindow{ {static_cast<unsigned int>(width), static_cast<unsigned int>(height)}, "ChessToolKit"};
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);
    DrawingCanvas canvas{width, height};
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
            if (event.type == sf::Event::Resized) {
                if(event.size.width < 512 || event.size.height < 512) {
                    resize(width, height, &window, &canvas);
                }else {
                    width = static_cast<int>(event.size.width);
                    height = static_cast<int>(event.size.height);
                    resize(width, height, &window, &canvas);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                clickHandler.analyzeMouseInput(event.mouseButton.x, event.mouseButton.y, &canvas, &event);
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
