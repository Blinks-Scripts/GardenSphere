#ifndef GAMECLASS_H
#define GAMECLASS_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <ncurses.h>
#include "playerclass.h"
#include "timer.h"
#include "building.h"

class GAME {
    public:
		WORLD_MAP* world_map;
        PLAYER* player;
        WINDOW* main_win = stdscr;
        TIMER* g_clock;

        GAME();
        //GAME( int file_descriptor );
        ~GAME();

        int run();
    
};

GAME::GAME() {
    player = new PLAYER();
    g_clock = new TIMER();
    
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
};

int GAME::run() {
    int ch = 'r';
    while ( ch != 'q' ) {
        erase();
        player->receive_command( ch );
        player->draw_self();   
        g_clock->update();
        mvaddstr( 2, 70, g_clock->time_str() );
        refresh();

        halfdelay(5);        
        ch = getch();
    }

    endwin();

    return 1;
}

GAME::~GAME()
{
    std::cout << "game destructor\n";
    delete player;
    delete g_clock;
    return;
}

#endif
