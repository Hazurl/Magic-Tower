#include <Utilities/GameEngine.h>
#include <SFML/Graphics.hpp>
#include <Utilities/RessourcesLoader.h>
#include <cstdlib>
#include <ctime>

int main (int , char** ) {
    srand(time(NULL));

    FontLoader::useAllocator([] (std::string const& path) {
        auto f = new sf::Font();
        f->loadFromFile(path);
        return f;
    });
    TextureLoader::useAllocator([] (std::string const& path) {
        auto t = new sf::Texture();
        t->loadFromFile(path);
        return t;
    });

    GameEngine game;
    return game.start();
}