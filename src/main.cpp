#include <Utilities/GameEngine.h>
#include <SFML/Graphics.hpp>
#include <Utilities/RessourcesLoader.h>
#include <cstdlib>
#include <ctime>

int main (int , char** ) {
    srand(time(NULL));

    GameEngine game;
    return game.start();
}