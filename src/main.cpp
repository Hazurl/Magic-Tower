#include <Utilities/GameEngine.h>

#include <cstdlib>
#include <ctime>

int main (int , char** ) {
    srand(0);
    GameEngine game;
    return game.start();
}