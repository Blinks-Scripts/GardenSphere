#ifndef GAMECLASS_H
#define GAMECLASS_H

#include "playerclass.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <ncurses.h>
#include "clock.h"

class GAME {
    public:
        PLAYER* player;
        WINDOW* main_win = stdscr;
        GAMECLOCK* g_clock;

        GAME();
        //GAME( int file_descriptor );
        ~GAME();

        int run();
    
};

GAME::GAME() {
    player = new PLAYER();
    player->pos = std::pair<int,int>(10,10);
    std::cout << "Enter a player name: " << std::endl;
    std::string pl_name;
    std::cin >> pl_name;
    player->ch_name( pl_name );

    g_clock = new GAMECLOCK();
    BUILDING* house = new BUILDING();

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
};

int GAME::run() {
    int ch = 'r';

    while ( ch != 'q' ) {
        switch ( ch ) {
            case KEY_UP: player->pos.first -= 1; 
                         player->incr_step();
                         break;
            case KEY_DOWN: player->pos.first += 1; 
                           player->incr_step();
                           break;
            case KEY_LEFT: player->pos.second -= 1;
                           player->incr_step();
                           break;
            case KEY_RIGHT: player->pos.second += 1;
                            player->incr_step();
                            break;
            default: break;
        };
        erase();

        house.draw_self(); 

        // draw player
        move(player->pos.first, player->pos.second);
        addch(player->pl_symbol);
        addch(' ');
        addstr( player->get_step_str() );

        // draw clock
        mvaddstr( 2, 40, (std::to_string( g_clock->game_time )).c_str() );
        
        halfdelay(1);
        g_clock->update();
        refresh();

                
        ch = getch();
    }

    endwin();

    return 1;
}

GAME::~GAME()
{
    std::cout << "game desctructor\n";
    delete player;
    return;
}

#endif
