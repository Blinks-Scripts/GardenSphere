#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H

#include <utility>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include "ncurses.h"
#include "location.h"
#include "worldmap.h"

class PLAYER {
    public:
        //JFXLIB* graphics_lib;
        WORLD_MAP* world_map;

        std::pair<int,int> pos; // y, x position within a map tile
        std::pair<int,int> world_tile = {0,0}; // coordinate of map tile in which player is located
        std::string name = "default"; // Player Name
        char pl_symbol = 'o'; // Image of player
        int step_count = 0; // Distance moved by player
        LOCATION* location; // Current map tile of the player
       

        PLAYER(); // Default constructor
        PLAYER( std::pair<int,int> ); // Constructor to initiateplayer position
        ~PLAYER(); // Destructor

		// Player movement methods
        void move_up(); void move_down();
        void move_left(); void move_right();

        void receive_command( int ); // Receive command and process
        void print_pos(); // Print player position
        void ch_name( std::string& ); // Change player name
        void incr_step(); // Increase step count by 1
        void incr_step( size_t n ); // Increase step count by n
        const char* get_step_str(); // Return step count as std::string

};

/**
 * Default constructor
 * 
 * Initiate a WORLD_MAP() object
 * Get initial player LOCATION from
 * world_map
 * 
 **/
PLAYER::PLAYER()
{
    pos = {0,0};
    world_tile = { 0, 0 };
    //graphics_lib = new JFXLIB();
    world_map = new WORLD_MAP();

    location = world_map->get_location( world_tile );
}

/**
 * Construct player at coordinate p
 **/
PLAYER::PLAYER( std::pair<int,int> p )
{
    pos = p;
}

/**
 * Destructor
 **/
PLAYER::~PLAYER()
{
    std::cout << "player destructor\n";
    return;
}

/**
 * change the name of the player
 * 
 * This also changes the symbol used for the player
 **/
void PLAYER::ch_name( std::string& n )
{
    name = n;
    pl_symbol = name[0];
}


/**
 * move_up(), move_down(), move_left(), move_right()
 * 
 * move the player 1 char in the respective direction
 * check for tile edge crossing and place the new tile's
 * LOCATION as the PLAYER's location
 * 
 * collisions with objects not implemented yet
 ****/
void PLAYER::move_up()
{
    if ( pos.first > 1 ) {
        pos.first -= 1;
    } else if ( pos.first == 1 ) {
        pos.first = 20;
        world_tile.first -= 1;
        location = world_map->get_location( world_tile );

    } // else if ( collision( (player.pos.first - 1), (player.pos.second) )

    incr_step();
}

void PLAYER::move_down()
{
    if ( pos.first < 20 ) {
        pos.first += 1;
    } else if ( pos.first == 20 ) {
        pos.first = 1;
        world_tile.first += 1;
        location = world_map->get_location( world_tile );

    } // else if ( collision( (player.pos.first - 1), (player.pos.second) )

    incr_step();
}

void PLAYER::move_left()
{
    if ( pos.second > 1 ) {
        pos.second -= 1;
    } else if ( pos.second == 1 ) {
        pos.second = 40;
        world_tile.second -= 1;
        location = world_map->get_location( world_tile );

    } // else if ( collision( (player.pos.first - 1), (player.pos.second) )

    incr_step();
}

void PLAYER::move_right()
{
    if ( pos.second < 40 ) {
        pos.second += 1;
    } else if ( pos.second == 40 ) {
        pos.second = 1;
        world_tile.second += 1;
        location = world_map->get_location( world_tile );

    } // else if ( collision( (player.pos.first - 1), (player.pos.second) )

    incr_step();
}

/**
 * receive a command from (usually, currently always) the GAME object 
 * and process it accordingly.
 * 
 * movement:  up, down, left, right implemented
 * 
 * uses <ncurses.h> constants
 **/
void PLAYER::receive_command( int c )
{
    switch( c ) {

        case KEY_UP: move_up(); break;
        case KEY_DOWN: move_down(); break;
        case KEY_LEFT: move_left(); break;
        case KEY_RIGHT: move_right(); break;
        default: break;
    };
}

/**
 * print the player position y, x
 ***/
void PLAYER::print_pos() {
    std::cout << name << " y = " << pos.first << std::endl;
    std::cout << std::string(this->name.length(), ' ') << " x = " << pos.second << std::endl;
}

/**
 * increase step counter by 1
 * */
void PLAYER::incr_step() {
    step_count += 1;
}

/**
 * increase step counter by n
 **/
void PLAYER::incr_step( size_t n ) 
{
    step_count += n;
}

/**
 * convert step counter to c-string and return it
 **/
const char* PLAYER::get_step_str()
{
    std::string step_str = std::to_string( step_count );
    return step_str.c_str();
}

#endif
