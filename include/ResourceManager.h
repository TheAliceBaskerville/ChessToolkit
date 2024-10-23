#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <unordered_map>
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "TexturesName.h"

class ResourceManager
{
    private:
        std::unordered_map<std::string, sf::Font> fonts;
        std::unordered_map<TexturesName, sf::Texture> textures;
        constexpr std::string pathFonts{"../fonts/"};
        constexpr std::string pathTextures{"../resources/textures/"};
        constexpr std::string pathThemes{"../themes/"};
        std::string defaultTheme, pieceAssets, defaultAssets, defaultFont;
        json theme;
        sf::Color defaultColor;
        ResourceManager& checkDefaultResources();
    public:
        ResourceManager(const std::string& theme, const std::string& pieceAssets);
        ~ResourceManager() = default;
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager(ResourceManager&&) = default;
        ResourceManager& operator=(const ResourceManager&) = delete;
        ResourceManager& operator=(ResourceManager&&) = default;

        ResourceManager& loadFont(const std::string& name);
        sf::Font& getFont(const std::string& name);
        ResourceManager& unloadFont(const std::string& name);

        ResourceManager& loadTexture(TexturesName name);
        sf::Texture& getTexture(TexturesName name);
        ResourceManager& unloadTexture(TexturesName name);

        ResourceManager& setTheme(const json& theme);

        ResourceManager& setPieceAssets(const string& assets);
};

#endif