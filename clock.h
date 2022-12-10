#ifndef CLOCK_H
#define CLOCK_H

#include <time.h>
#include <cstdlib>

class GAMECLOCK {

    public:
        double game_time;
        time_t start_time;

        GAMECLOCK();
        ~GAMECLOCK();
        void update();

};

GAMECLOCK::GAMECLOCK() 
{
    time( &start_time );
    game_time = difftime( time(NULL), start_time );
}

GAMECLOCK::~GAMECLOCK() 
{}

void GAMECLOCK::update() {

    game_time = difftime( time(NULL), start_time );
}

#endif
