#ifndef __RESSOURCES_LOADER
#define __RESSOURCES_LOADER

#include <SFML/Graphics.hpp>
#include <frameworkHaz/Interface/RessourceLoader.hpp>

class FontAllocator : public haz::Allocator<sf::Font, std::string> {
public:
    sf::Font* allocate(std::string s) override {
        auto f = new sf::Font();
        f->loadFromFile(s);
        return f;
    }

    void deallocate (sf::Font* font) override {
        delete font;
        font = nullptr;
    }
};

class TextureAllocator : public haz::Allocator<sf::Texture, std::string> {
public:
    sf::Texture* allocate(std::string s) override {
        auto f = new sf::Texture();
        f->loadFromFile(s);
        return f;
    }

    void deallocate (sf::Texture* texture) override {
        delete texture;
        texture = nullptr;
    }
};

typedef haz::RessourceLoader<sf::Font,      std::string,    std::string,    std::string,    FontAllocator>      FontLoader;
//                           type           argAlloc        Key             scene Key       Allocator
typedef haz::RessourceLoader<sf::Texture,   std::string,    std::string,    std::string,    TextureAllocator>   TextureLoader;

#endif