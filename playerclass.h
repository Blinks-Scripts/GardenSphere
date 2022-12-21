#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H

#include <utility>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <map>
#include <math.h>
#include <vector>
#include <deque>
#include "ncurses.h"
#include "location.h"
#include "worldmap.h"
#include "constants.h"
#include "position.h"
#include "timer.h"

class PLAYER {
    public:
    
		std::string name; // Player Name

        POSITION* pos; // screen coordinates, world coordinates, WORLD_MAP object
        TIMER* img_timer;
        std::map<std::string, std::deque<ITEM*>> inventory;
        
        std::vector<std::vector<std::string>> player_sprites; // frames of the player image
        std::vector<std::string>* player_image; // pointer to a single player sprite
        
        char player_dir;
		
        void load_sprites( std::string ); // load sprites from a file
        void change_sprite( int ); // change the current sprite
        
        void change_direction( int );
        int get_drop_pY(); // Get the placement Y coordinate of the player
        int get_drop_pX(); // Get the placement X coordinate of the player
        
        void receive_command( int ); // Receive command and process
        
		// Player movement methods
        void move_player( int );
        bool check_all_impasses( int, int );
        bool legal_move( int, int );
        
        void draw_self();
        void draw_hud();
                
        PLAYER(); // Default constructor
        ~PLAYER(); // Destructor
      
        std::string itm_sel = " ";
        std::string inc_selection();
        void place_item();
        void place_item( int, int, ITEM* );
        void place_item( int, int, std::deque<ITEM*>& );
        void grab_item( int, int );


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
	std::cout << "player constructor entered\n";
	pos = new POSITION( DEFAULT_PY, DEFAULT_PX );
	img_timer = new TIMER();
    
    player_sprites.resize(8);
    load_sprites( DEFAULT_PLAYER_SPRITES );
    change_direction( KEY_DOWN );

    
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
	}
}

/**
 * Destructor
 **/
PLAYER::~PLAYER()
{
	delete img_timer;
	img_timer = NULL;
	delete pos;
	pos = NULL;
}


void PLAYER::load_sprites( std::string filename )
{
	std::vector<std::string>* p_sprites = &player_sprites[UP];

	// Open the file for reading
	std::ifstream pf(filename); // pf (aka playerfile)

	// Check if the file was successfully opened
	if (!pf) {
		std::cerr << "Error: Unable to open file " << filename << std::endl;
		return;
	}
	
	// Read the contents of the file into a string
	std::string line;
	while (std::getline(pf, line)) {
		if (line == ":" ) {
			p_sprites++; // move to the next sprite container
		} else {
			//line.erase(line.size()-1); // remove \n char
			p_sprites->push_back(line); // push line into current sprite
		}
	}
}

void PLAYER::change_direction( int direction )
{
	int new_player_dir;
	switch( direction ) {
		case KEY_UP: new_player_dir = UP; break;
		case KEY_DOWN: new_player_dir = DOWN; break;
		case KEY_LEFT: new_player_dir = LEFT; break;
		case KEY_RIGHT: new_player_dir = RIGHT; break;
		default: break;
	};
	
	player_dir = new_player_dir;
	change_sprite( direction );
}

void PLAYER::change_sprite( int direction )
{
	switch(direction) {
		case KEY_UP: player_image = &player_sprites[UP]; break;
		case KEY_DOWN: player_image = &player_sprites[DOWN]; break;
		case KEY_LEFT: player_image = &player_sprites[LEFT]; break;
		case KEY_RIGHT: player_image = &player_sprites[RIGHT]; break;
		default: player_image = &player_sprites[RIGHT]; break;
	};
}

int PLAYER::get_drop_pY()
{
	int tempY;
	
	if (player_dir == UP) tempY = pos->pY - 1;
    else if (player_dir == DOWN) tempY = pos->pY + 3;
	else if (player_dir == LEFT) tempY = pos->pY + 2;
    else if (player_dir == RIGHT) tempY = pos->pY + 2;
    else tempY = pos->pY; // default case
	
	return tempY;
}

int PLAYER::get_drop_pX()
{
	int tempX;
	
    if (player_dir == UP) tempX = pos->pX;
    else if (player_dir == DOWN) tempX = pos->pX;
	else if (player_dir == LEFT) tempX = pos->pX - 4;
    else if (player_dir == RIGHT) tempX = pos->pX + 4;
    else tempX = pos->pX; // default case
    
    return tempX;
}

bool PLAYER::check_all_impasses( int tile_y, int tile_x )
{
	if ( player_dir == UP || player_dir == DOWN ) {
		for ( int i = -2; i < 3; i++ ) {
			if ( pos->location->collision_is_impasse( tile_y, tile_x + i ) ) return true;
		}
	} else if ( player_dir == LEFT || player_dir == RIGHT ) {
		for ( int i = 0; i < 3; i++ ) {
			if ( pos->location->collision_is_impasse( tile_y - i, tile_x ) ) return true;
		}
	}
	return false;
}

bool PLAYER::legal_move( int tile_y, int tile_x )
{
	if ( check_all_impasses( tile_y, tile_x ) ) {
		return false;
	}
	
	if ( (tile_y < BORDERTOP && pos->getWY() == WORLDTOP) ||
	     (tile_y > BORDERBOTTOM && pos->getWY() == WORLDBOTTOM) ||
	     (tile_x < BORDERLEFT && pos->getWX() == WORLDLEFT) ||
	     (tile_x > BORDERRIGHT && pos->getWX() == WORLDRIGHT) ) return false;
	return true;
}

void PLAYER::move_player( int direction )
{
	int tempY = 0;
	int tempX = 0;
	
	switch( direction ) {
		case KEY_UP: tempY = -1; break;
		case KEY_DOWN: tempY = 1; break;
		case KEY_LEFT: tempX = -1; break;
		case KEY_RIGHT: tempX = 1; break;
		default: break;
	};
	
	change_direction( direction );
	
	
	// The potential move doesn't have barrier collisions and
	// any necessary map tile is available
	if ( legal_move( get_drop_pY(), get_drop_pX() ) ) {
		pos->pY += tempY;
		pos->pX += tempX;
	} else return;
	
	// If player has crossed a tile border
	if ( pos->pY < BORDERTOP || pos->pY > BORDERBOTTOM || 
	     pos->pX < BORDERLEFT || pos->pX > BORDERRIGHT ) {
		// update world coordinates to new tile
		pos->incrWYX( tempY, tempX );
		// Change plater position to opposite end of screen
		if ( tempY != 0 )
			pos->pY = std::abs( pos->pY - (BORDERBOTTOM - BORDERTOP) ) + tempY;
		if ( tempX != 0 )
			pos->pX = std::abs( pos->pX - (BORDERRIGHT - BORDERLEFT) ) + tempX;		
	}
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
 * places an item into player's LOCATION object
 * at the player coordinates within the LOCATION
 ***/

void PLAYER::place_item()
{
	ITEM* itm = new ITEM( "apple", false );
	int placement_Y = get_drop_pY();
	int placement_X = get_drop_pX();
	pos->location->add_item( placement_Y, placement_X, itm );
}


void PLAYER::place_item( int Y, int X, ITEM* itm )
{
	pos->location->add_item( Y, X, itm );
}

void PLAYER::place_item( int Y, int X, std::deque<ITEM*>& itm_deq )
{
	// initial empty()-catch is intended to be the deque at key: "empty inventory"
	// should always be empty
	if ( itm_deq.empty() ) return; // only executes (or skips the method, more appropriately) if inventory is empty
	ITEM* itm = itm_deq.front();
	itm_deq.pop_front();
	// if deque is empty, inc selection
	pos->location->add_item( Y, X, itm );
	if ( itm_deq.empty() ) itm_sel = inc_selection();
}

void PLAYER::grab_item( int Y, int X ) {
	std::deque<ITEM*>* item_pile = pos->location->get_item_pile( Y, X );
	if ( item_pile != NULL ) {
		ITEM* top_item = item_pile->back();
		if ( item_pile->size() > 0 ) {
			inventory[top_item->item_name].push_back(top_item);
			if ( itm_sel == "empty inventory" ) itm_sel = top_item->item_name;
			item_pile->pop_back();
		}
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

        case KEY_UP: move_player(c); break;
        case KEY_DOWN: move_player(c); break;
        case KEY_LEFT: move_player(c); break;
        case KEY_RIGHT: move_player(c); break;
        case ']': itm_sel = inc_selection(); break;
        case 'p': place_item( get_drop_pY(), get_drop_pX(), inventory[itm_sel] ); break;
        case 'a': place_item(); break;
        //case 'o': place_item( pos, new ITEM( "!fence", true )); break;
        case 'g': grab_item( get_drop_pY(), get_drop_pX() );
        default: break;
    };
}

/**
 * print the player position y, x
 ***/

void PLAYER::draw_self()
{	
	pos->location->draw_self();
	
	// Frame A of player sprites are the first 4 vectors, Frame B of player sprites are next 4
	// alternate frames A and B each second
	size_t subsprite_offset = 0;
	if( img_timer->get_elapsed() % 2 == 0 ) { subsprite_offset = 0; }
	else {subsprite_offset = 4;}
	
	size_t drawY = pos->pY;
	size_t drawX = pos->pX - 3;

	for ( size_t i = 0; i < 3; i++ ) {
		// draw each line of the player image
		mvaddstr( drawY + i, drawX, (player_image + subsprite_offset)->at(i).c_str() );
	}
	
	draw_hud();
}

void PLAYER::draw_hud()
{
	int temp = 1;
	move(HUDY,HUDX);
	for ( int i = 0; i < HUDW; i++ )
	{
		addch('-');
	}
	move(HUDY+HUDH,HUDX);
	for ( int i = 0; i < HUDW; i++ )
	{
		addch('-');
	}
	
	for ( int k = 1; k < HUDH; k++ ) {
		mvaddch( HUDY+k, HUDX, '{' );
		mvaddch( HUDY+k, HUDX+HUDW, '}' );
	}
	
	//draw inventory
	for ( auto i : inventory ) {
		// if the item count is 0, do not list the item in inventory
		// the key is still in the map even if item count is 0 so we need to check item count
		if ( (int)(i.second.size()) == 0 ) continue; // skip the item and don't increase temp
		mvaddstr( HUDY+temp+1, HUDX+2, i.first.c_str() );
		mvaddstr( HUDY+temp+1, HUDX+HUDW-5, std::to_string(i.second.size()).c_str() );
		if ( i.first == itm_sel ) addstr("--");
		temp++; 
	}
}





#endif
