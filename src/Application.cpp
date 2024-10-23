#include <unordered_set>
#include <fstream>
#include "TexturesName.h"
#include "Application.h"

static constexpr std::unordered_set<TexturesName> requiredTextures {
    TexturesName::BACKGROUND,
    TexturesName::HIGHLIGHT,
    TexturesName::CONTROL_FOCUSED,
    TexturesName::CONTROL_UNFOCUSED
};

Application::Application() {

    Context.menuContext = MenuContext{};
    
    std::ifstream settingsFile("../settings.json");
    json settings = json::parse(settingsFile);
    settingsFile.close();

    window = sf::RenderWindow{sf::VideoMode{settings["windowWidth"], settings["windowHeight"]},
     "ChessToolKits", sf::Style::Titlebar | sf::Style::Close};

    resourceManager = ResourceManager{settings["theme"], settings["piecesAssets"]};
    resourceManager.loadFont(settings["mainFont"]);
    for (TexturesName texture : requiredTextures) {
        resourceManager.loadTexture(texture);
    }
}

void Application::run() {

}