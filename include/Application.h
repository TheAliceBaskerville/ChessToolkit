#ifndef APPLICATION_H
#define APPLICATION_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "ResourceManager.h"
#include "Contexts.h"

class Application {
    private:
        ResourceManager resourceManager;
        sf::RenderWindow window;
        Contexts Context;
    public:
        Application();
        ~Application() = default;
        Application(const Application&) = delete;
        Application(Application&&) = default;
        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = default;
        void run();
}

#endif