#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <cstdlib>
#include <algorithm>
#include <vector>
#include <utility>
#include <deque>
#include <iostream>
#include <ncurses.h>
#include "item.h"


class COLLISIONS {
	public:
	
	std::vector<char> collisions; // W == wall, H == hole, future implementaiton may have collision types class
	std::deque<ITEM*> items;
	bool impasse_bool = false;
	
	COLLISIONS();
	COLLISIONS( ITEM* );
	~COLLISIONS();
	
	void add_item( ITEM* );
	ITEM* remove_item();
	std::deque<ITEM*>* get_item_pile_pointer();
	bool impasse(); // check if coordinate is traversable
	void draw_self( int, int );
	
};

COLLISIONS::COLLISIONS() {
	collisions.push_back('W');
}

COLLISIONS::COLLISIONS( ITEM* initial_item )
{
	if ( initial_item->itm_symbol != ' ' ) {
		items.push_back( initial_item );
	}
	else { delete initial_item ; }
}

COLLISIONS::~COLLISIONS() {}

void COLLISIONS::add_item( ITEM* item )
{
	items.push_back( item );
}

ITEM* COLLISIONS::remove_item()
{
	ITEM* top_item = items.back();
	items.pop_back();
	return top_item;
}

std::deque<ITEM*>* COLLISIONS:: get_item_pile_pointer()
{
	if ( items.empty() ) {
		return NULL;
	}
	std::deque<ITEM*>* item_pile = &items;
	return item_pile;
}

// refactor this, it's so wonky
bool COLLISIONS::impasse()
{
	//std::cout << "checking root impass \n";
	//if ( impasse_bool ) return true;
	if ( collisions.empty() ) return false;
	if ( ! collisions.empty() ) {
		// if we dont find a 'W', return false. Is not an impasse
		if ( std::find_if( collisions.begin(), collisions.end(), []( char& c ){ return (c == 'W'); } ) == collisions.end() )
		{
			return false;
		}
	}
	
	return true;
}

void COLLISIONS::draw_self( int Y, int X )
{
	if ( items.empty() ) return;
	
	char top_item = items.back()->itm_symbol;
	mvaddch( Y, X, top_item );
}

#endif
