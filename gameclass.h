#ifndef GAMECLASS_H
#define GAMECLASS_H

#include "playerclass.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <ncurses.h>
#include "clock.h"
#include "building.h"
#include "location.h"
#include "jfxlib.h"

class GAME {
    public:
        PLAYER* player;
        WINDOW* main_win = stdscr;
        GAMECLOCK* g_clock;
        JFXLIB* graphics_lib;
        LOCATION* current_location;


        //BUILDING* house;

        GAME();
        //GAME( int file_descriptor );
        ~GAME();

        int run();
        void draw_board( LOCATION* );
    
};

GAME::GAME() {
    player = new PLAYER();
    player->pos = std::pair<int,int>(10,10);
    std::cout << "Enter a player name: " << std::endl;
    std::string pl_name;
    std::cin >> pl_name;
    player->ch_name( pl_name );  
    //current_location = new LOCATION( "home.tile", graphics_lib );

    g_clock = new GAMECLOCK();
    //house = new BUILDING();
    

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
};

void GAME::draw_board( LOCATION* loc )
{
    loc->draw_self();
    //draw_hud();   
}

int GAME::run() {
    int ch = 'r';
    while ( ch != 'q' ) {
        erase();
        player->receive_command( ch );
        draw_board( player->location );

        // draw player
        move(player->pos.first, player->pos.second);
        addch(player->pl_symbol);
        addch(' ');
        addstr( player->get_step_str() );

        // draw clock
        mvaddstr( 2, 40, (std::to_string( g_clock->game_time )).c_str() );
        
        halfdelay(5);
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
