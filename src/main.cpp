#include "Header/Utilities/GameEngine.h"

#include <cstdlib>
#include <ctime>

int main (int , char** ) {
    srand(time(NULL));
    GameEngine game;
    return game.start();
}