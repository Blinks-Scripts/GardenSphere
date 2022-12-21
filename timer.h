#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <cstdlib>
#include <string>

class TIMER {

    public:

        TIMER();
        ~TIMER();
        
        void start_clock();
        void stop_clock();
        void update();
        const char* time_str();
        size_t get_elapsed();
        int get_elapsed_int();
        size_t get_unelapsed();
        
    private:
    
        size_t elapsed_time;            // Time spent with clock active
        size_t unelapsed_time      = 0; // Time spent with clock inactive
        time_t start_time; // the SYSTEM time at instantiation of this object
        time_t pause_event_time    = 0; // the SYSTEM time at clock stoppage,
        size_t pause_unelapsed_buf = 0; // accrued time of current clock stoppage, to be added to unelapsed upon clock resume
        
        
        size_t _get_total_time(); // elapsed_time + unelapsed_time
        size_t _get_elapsed_time(); // current time - unelapsed_time
        int _get_elapsed_time_int();
        size_t _get_unelapsed_time(); // aggregated during clock stoppage with update()
        size_t _get_start_time(); // SYSTEM time at instantiation
        size_t _get_pause_event_time(); // stays current with SYSTEM time while clock is stopped
        
        void _update();

};

TIMER::TIMER() 
{
    time( &start_time ); // Put current SYSTEM time into start_time
    elapsed_time = difftime( time(NULL), start_time ) - unelapsed_time; // ( nowtime - starttime ) - ( time spent paused )
}

TIMER::~TIMER() 
{}

void TIMER::start_clock()
{
	// if clock is not already running
	if ( pause_event_time != 0 ) {
		// add the time spent paused to unelapsed time
		unelapsed_time += pause_unelapsed_buf;
		// reset pause_time and use 0 as a flag
		pause_event_time = 0;
	}
}

void TIMER::stop_clock()
{
	// set the time at which clock was stopped
	time( &pause_event_time );
}

size_t TIMER::get_elapsed() 
{
	return ( _get_elapsed_time() );
}

int TIMER::get_elapsed_int()
{
	return ( _get_elapsed_time_int() );
}

size_t TIMER::get_unelapsed() 
{
	return ( _get_unelapsed_time() );
}

size_t TIMER::_get_total_time()
{
	update();
	return ( elapsed_time + unelapsed_time );
}

size_t TIMER::_get_elapsed_time()
{
	update();
	return ( elapsed_time );
}

int TIMER::_get_elapsed_time_int()
{
	return (int)( elapsed_time );
}

size_t TIMER::_get_unelapsed_time()
{
	update();
	return ( unelapsed_time );
}

size_t TIMER::_get_start_time()
{
	return ( start_time );
}

size_t TIMER::_get_pause_event_time()
{
	return ( pause_event_time );
}

const char* TIMER::time_str()
{
	// return elapsed_time (the game time) as a string
	return (std::to_string( elapsed_time ) ).c_str();
}

void TIMER::update()
{
	_update();
}

void TIMER::_update() 
{
	// if clock is running (not paused)
	if ( pause_event_time == 0 ) {
		// update the elapsed time
		elapsed_time = difftime( time(NULL), start_time ) - unelapsed_time;
	} else if ( pause_event_time != 0 ) // if clock is stopped
	  { 
		// keep pause_unelapsed_buf time updated
		pause_unelapsed_buf = difftime( time(NULL), pause_event_time );
	}
}

#endif
