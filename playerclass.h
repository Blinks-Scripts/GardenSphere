#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H

#include <utility>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <map>
#include <deque>
#include "ncurses.h"
#include "location.h"
#include "worldmap.h"
#include "item.h"

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
        
        std::map<std::string, std::deque<ITEM*>> inventory;
        int hudy = 10;
        int hudx = 70;
        int hudh = 20;
        int hudw = 20;
        
        std::string itm_sel;
       

        PLAYER(); // Default constructor
        PLAYER( std::pair<int,int> ); // Constructor to initiateplayer position
        ~PLAYER(); // Destructor

		// Player movement methods
        void move_up(); void move_down();
        void move_left(); void move_right();
        void place_item();
        void place_item( std::pair<int,int>, ITEM* );
        void place_item( std::pair<int,int>, std::deque<ITEM*>& );
        void grab_item( std::pair<int,int>, std::deque<ITEM*>& );
        
        std::string inc_selection();

        void receive_command( int ); // Receive command and process
        void print_pos(); // Print player position
        void ch_name( std::string& ); // Change player name
        void incr_step(); // Increase step count by 1
        void incr_step( size_t n ); // Increase step count by n
        const char* get_step_str(); // Return step count as std::string
        
        void draw_hud();

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
    
    for ( int i = 0; i < 3; i++ ) {
		ITEM* itm = new ITEM( "apple", false );
		inventory[itm->item_name].push_back(itm);
	}
	
	for ( int i = 0; i < 3; i++ ) {
		ITEM* itm = new ITEM( "banana", false );
		inventory[itm->item_name].push_back(itm);
	}
	
	if ( ! inventory.empty() ) {
		for ( auto firstItem : inventory ) {
			itm_sel = firstItem.first;
			break;
		}
	} else {
		itm_sel = " ";
	}

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
 * 
 ****/
void PLAYER::move_up()
{
	// check collisions
	std::pair<int,int> try_pos = std::make_pair( pos.first-1, pos.second );
	location->add_item_collision( try_pos, new ITEM( " ", false ) );
	if ( location->collisions[try_pos] != NULL ) {
		if ( location->collisions[try_pos]->impasse() ) return;
	}
	
	// check legality
    if ( pos.first > 1 ) {
        pos.first -= 1;
    } else if ( pos.first == 1 ) {
        pos.first = 20;
        world_tile.first -= 1;
        location = world_map->get_location( world_tile );
        // need another collision check in here in case we collide on next map tile

    } 

    incr_step();
    pl_symbol = '^';
}

void PLAYER::move_down()
{
	std::pair<int,int> try_pos = std::make_pair( pos.first+1, pos.second );
	location->add_item_collision( try_pos, new ITEM( " ", false ) );
	if ( location->collisions[try_pos] != NULL ) {
		if ( location->collisions[try_pos]->impasse() ) return;
	}
    if ( pos.first < 20 ) {
        pos.first += 1;
    } else if ( pos.first == 20 ) {
        pos.first = 1;
        world_tile.first += 1;
        location = world_map->get_location( world_tile );

    } // else if ( collision( (player.pos.first - 1), (player.pos.second) )

    incr_step();
    pl_symbol = 'v';
}

void PLAYER::move_left()
{
	std::pair<int,int> try_pos = std::make_pair( pos.first, pos.second-1 );
	location->add_item_collision( try_pos, new ITEM( " ", false )  );
	if ( location->collisions[try_pos] != NULL ) {
		if ( location->collisions[try_pos]->impasse() ) return;
	}
    if ( pos.second > 1 ) {
        pos.second -= 1;
    } else if ( pos.second == 1 ) {
        pos.second = 65;
        world_tile.second -= 1;
        location = world_map->get_location( world_tile );

    } // else if ( collision( (player.pos.first - 1), (player.pos.second) )

    incr_step();
    pl_symbol = '<';
}

void PLAYER::move_right()
{
	std::pair<int,int> try_pos = std::make_pair( pos.first, pos.second+1 );
	location->add_item_collision( try_pos, new ITEM( " ", false ) );
	if ( location->collisions[try_pos] != NULL ) {
		if ( location->collisions[try_pos]->impasse() ) return;
	}
    if ( pos.second < 65 ) {
        pos.second += 1;
    } else if ( pos.second == 65 ) {
        pos.second = 1;
        world_tile.second += 1;
        location = world_map->get_location( world_tile );

    } // else if ( collision( (player.pos.first - 1), (player.pos.second) )

    incr_step();
    pl_symbol = '>';
}

/**
 * places an item into player's LOCATION object
 * at the player coordinates within the LOCATION
 ***/
void PLAYER::place_item()
{
	ITEM* itm = new ITEM( "apple", false );
	location->add_item_collision( pos, itm );
}

void PLAYER::place_item( std::pair<int,int> coords, ITEM* itm )
{
	location->add_item_collision( coords, itm );
}

void PLAYER::place_item( std::pair<int,int> coords, std::deque<ITEM*>& itm_deq )
{
	// initial empty()-catch is intended to be the deque at key: "empty inventory"
	// should always be empty
	if ( itm_deq.empty() ) return; // only executes (or skips the method, more appropriately) if inventory is empty
	ITEM* itm = itm_deq.front();
	itm_deq.pop_front();
	// if deque is empty, inc selection
	location->add_item_collision( coords, itm );
	if ( itm_deq.empty() ) itm_sel = inc_selection();
}

void PLAYER::grab_item( std::pair<int,int>, std::deque<ITEM*>& item_pile ) {
	if ( item_pile.size() > 0 ) {
		inventory[item_pile.front()->item_name].push_back(item_pile.front());
		if ( itm_sel == "empty inventory" ) itm_sel = item_pile.front()->item_name;
		item_pile.pop_front();
	}
	
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
        case ']': itm_sel = inc_selection(); break;
        case 'p': place_item( pos, inventory[itm_sel] ); break;
        case 'o': place_item( pos, new ITEM( "!fence", true )); break;
        case 'g': grab_item( pos, location->collisions[pos]->items );
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

std::string PLAYER::inc_selection()
{
	bool flag = false;
	while ( ! inventory.empty() ) {
		for ( auto i = inventory.begin(); i != inventory.end(); ++i ) {
			if ( flag && ((int)(i->second.size()) > 0 )) return (i->first);
			if (i->first == itm_sel) {
				if ( flag ) return "empty inventory";
				flag = true;
			}
			if ( (i == inventory.end()) && !(inventory.empty()) ) { 
				i = inventory.begin();
			}
		}
	}
	
	return "empty inventory";
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

void PLAYER::draw_hud()
{
	int temp = 1;
	move(hudy,hudx);
	for ( int i = 0; i < hudw; i++ )
	{
		addch('-');
	}
	move(hudy+hudh,hudx);
	for ( int i = 0; i < hudw; i++ )
	{
		addch('-');
	}
	
	for ( int k = 1; k < hudh; k++ ) {
		mvaddch( hudy+k, hudx, '{' );
		mvaddch( hudy+k, hudx+hudw, '}' );
	}
	
	//draw inventory
	for ( auto i : inventory ) {
		// if the item count is 0, do not list the item in inventory
		// the key is still in the map even if item count is 0 so we need to check item count
		if ( (int)(i.second.size()) == 0 ) continue; // skip the item and don't increase temp
		mvaddstr( hudy+temp+1, hudx+2, i.first.c_str() );
		mvaddstr( hudy+temp+1, hudx+hudw-5, std::to_string(i.second.size()).c_str() );
		if ( i.first == itm_sel ) addstr("--");
		temp++; 
	}
}






#endif
