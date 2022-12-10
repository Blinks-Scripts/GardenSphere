#include "gameclass.h"

int main() {
    
    GAME mygame = GAME();
    std::cout << "game initialized\n";
    int gamestate = mygame.run();
    
    if ( gamestate == 1 )
        return 0;

    return 0;
}
