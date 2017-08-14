#ifndef __RESSOURCES_LOADER
#define __RESSOURCES_LOADER

#include <SFML/Graphics.hpp>
#include <frameworkHaz/Interface/RessourceLoader.hpp>

typedef haz::RessourceLoader<sf::Font, std::string, std::string, std::string> FontLoader;
typedef haz::RessourceLoader<sf::Texture, std::string, std::string, std::string> TextureLoader;

#endif