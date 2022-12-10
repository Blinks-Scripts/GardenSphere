#include "gameclass.h"

int main() {
    
    GAME mygame = GAME();
    std::cout << "game initialized\n";
    int gamestate = mygame.run();

    return 0;
}
