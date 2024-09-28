#include <SFML/Graphics.hpp>
#include <ClickHandler.h>
#include <KeyboardHandler.h>
#include <thread>
#include <functional>
#include "ClassicChessDrawer.h"
#include "ClassicChessCanvas.h"
#include "RenderThread.h"

// If this code works, it was written by Ruslan Fattakhov. If not,
// I don't know who wrote it

void resize(int width, int height, sf::RenderWindow* window, ClassicChessCanvas& canvas) {
    window->setSize(sf::Vector2u(static_cast<unsigned int>(width), static_cast<unsigned int>(height)));
    sf::FloatRect visibleArea(0, 0, width, height);
    window->setView(sf::View(visibleArea));
    ClassicChess::resize(width, height, canvas);
}

int main()
{
    int width = 512;
    int height = 512;
    sf::RenderWindow window = sf::RenderWindow{ {static_cast<unsigned int>(width), static_cast<unsigned int>(height)}, "ChessToolKit"};
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);
    
    ClassicChessCanvas canvas{width, height};
    ClassicChessCanvas& canvasPtr = canvas;

    ClickHandler clickHandler{&window, canvasPtr};
    KeyboardHandler keyboardHandler{&window, canvasPtr};

    window.setActive(false);
    bool isRunning = true;
    std::function<void()> closeRenderThread = [&]() {isRunning = false;};
    std::thread thread(RenderThread::renderClassicChessboard, std::ref(window), std::ref(canvas), std::ref(isRunning));
    thread.detach();

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                closeRenderThread();
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                if(event.size.width < 512 || event.size.height < 512) {
                    resize(width, height, &window, canvasPtr);
                }else {
                    width = static_cast<int>(event.size.width);
                    height = static_cast<int>(event.size.height);
                    resize(width, height, &window, canvasPtr);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                clickHandler.analyzeMouseInput(canvasPtr, &event);
            }
            if(event.type == sf::Event::KeyPressed) {
                keyboardHandler.analyzeKeyboardInput(&event);
            }
        }
    }
}
