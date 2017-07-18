#include "../Header/RessourcesLoader.h"

std::map<std::string, sf::Font*> RessourcesLoader::font_map = {};
std::map<std::string, sf::Texture*> RessourcesLoader::texture_map = {};

void RessourcesLoader::clearAll () {
    for (auto& font : font_map) {
        if (font.second)
            delete font.second;
    }
    for (auto& txt : texture_map) {
        if (txt.second)
            delete txt.second;
    }
    texture_map = {};
    font_map = {};
}