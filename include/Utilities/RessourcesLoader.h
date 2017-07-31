#ifndef __RESSOURCES_LOADER
#define __RESSOURCES_LOADER

#include <SFML/Graphics.hpp>
#include <cassert>

class RessourcesLoader {
public:
    template<class T>
    static const T* get(std::string const& name);

    template<class T>
    static const T* load(std::string const&, std::string const&);

    // TODO : release

    static void clearAll();

private:
    RessourcesLoader() = delete;
    ~RessourcesLoader() = delete;
    RessourcesLoader(const RessourcesLoader& ) = delete;

    static std::map<std::string, sf::Font*> font_map;
    static std::map<std::string, sf::Texture*> texture_map;
};


template<class T>
const T* RessourcesLoader::get(std::string const& name) {
    assert(("Ce type ne peut être chargé", false));
}

template<class T>
const T* RessourcesLoader::load(std::string const&, std::string const&) {
    assert(("Ce type ne peut être chargé", false));
}

template<>
inline const sf::Font* RessourcesLoader::load(std::string const& name, std::string const& filename) {
    if (font_map.find(filename) == font_map.end()) {
        sf::Font* font = new sf::Font();
        font->loadFromFile(filename);
        return font_map[name] = font;
    }
    return font_map[name];
}
template<>
inline const sf::Texture* RessourcesLoader::load(std::string const& name, std::string const& filename) {
    if (texture_map.find(filename) == texture_map.end()) {
        sf::Texture* texture = new sf::Texture();
        texture->loadFromFile(filename);
        return texture_map[name] = texture;
    }
    return texture_map[name];
}

template<>
inline const sf::Font* RessourcesLoader::get(std::string const& name) {
    return font_map[name];
}
template<>
inline const sf::Texture* RessourcesLoader::get(std::string const& name) {
    return texture_map[name];
}


#endif