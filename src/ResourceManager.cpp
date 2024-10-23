#include "ResourceManager.h"
#include <fstream>
#include "Defaulter.h"

ResourceManager::ResourceManager(const std::string& theme, const std::string& pieceAssets) 
: defaultTheme{"Light"}, defaultColor{sf::Color::Black}, defaultAssets{"classic"}, defaultFont{"impact2.ttf"} {

    checkDefaultResources();

    std::fstream themeFile(pathThemes + theme + ".json");
    json themeJson;
    if (!themeFile) {
        themeFile.close();
        themeFile.open(pathThemes + defaultTheme + ".json");
    }
    themeJson = json::parse(themeFile);
    themeFile.close();

    this->theme = themeJson;

    //тут нужна проверка наличия такой директории, но при этом надо убедиться, есть ли все файлы, или надо сказать дефолтеру о необходимости пересоздать файлы с фигурами.
    std::fstream pieceAssetsFile(pathTextures + pieceAssets);
    if (!pieceAssetsFile) {
        this->pieceAssets = defaultAssets;
    } else {
        this->pieceAssets = pieceAssets;
    }
}

ResourceManager& ResourceManager::checkDefaultResources() {
    std::fstream testFile(pathThemes + defaultTheme + ".json");
    if (!testFile) {
        Defaulter::createDefaultTheme();
    }
    testFile.close();
    testFile.open(pathFonts + defaultFont);
    if (!testFile) {
        Defaulter::createDefaultFont();
    }
    testFile.close();
    //тут нужна проверка наличия такой директории
    testFile.open(pathTextures + pieceAssets);
    if (!testFile) {
        Defaulter::createDefaultPiecesAssets();
    }
    testFile.close();
}

ResourceManager& ResourceManager::loadFont(const std::string& name) {
    fonts[name].loadFromFile(pathFonts + name);
    return *this;
}

sf::Font& ResourceManager::getFont(const std::string& name) {
    if (!fonts[name]) {
        loadFont(name);
    }
    return fonts.at(name);
}

ResourceManager& ResourceManager::unloadFont(const std::string& name) {
    fonts.erase(name);
    return *this;
}

ResourceManager& ResourceManager::loadTexture(TexturesName name) {
    // enum to string (toString псевдофункция)
    std::string stringName{toString(name)};
    std::string colorPiece{std::tolower(stringName.substr(0, 4))};

    //логику в enam? полумать над переопределением и повышением читабельности
    if (colorPiece != "black" || colorPiece != "white") {
        textures[name].loadFromFile(pathTextures + stringName);
    } else {
        textures[name].loadFromFile(pathTextures + pieceAssets + "/" + colorPiece + "/" + name);
    }
    
    if (!textures[name]) {
        sf::RenderTexture texture;
        texture.create(1, 1);
        sf::Color color{};

        //создать метод проверки темы и приведения темы к стандарту
        if (theme.contains(stringName)) {

            //могут быть проблемы с некорректным вводом данных (думаем над тем, как ловить exception)
            //посмотреть конвертацию в виде подключаемого файла
            std::stringstream rgb(theme[stringName]);
            std::string segment;
            std::vector<std::string> seglist;

            while(std::getline(rgb, segment, '.'))
            {
                seglist.push_back(segment);
            }

            color = sf::Color{rgb[0], rgb[1], rgb[2]};
        } else {
            color = defaultColor;
        }

        texture.clear(color);
        texture.setRepeated(true);
        textures[name] = texture.getTexture();
    }
    return *this;
}

sf::Texture& ResourceManager::getTexture(TexturesName name) {
    if(!textures[name]) {
        loadTexture(name);
    }
    return textures.at(name);
}

ResourceManager& ResourceManager::unloadTexture(TexturesName name) {
    textures.erase(name);
    return *this;
}

ResourceManager& ResourceManager::setTheme(const json& theme) {
    this->theme = theme;
    return *this;
}
