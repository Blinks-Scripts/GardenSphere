#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <cstdlib>
#include <algorithm>
#include <vector>
#include <utility>
#include <deque>
#include "item.h"


class COLLISIONS {
	public:
	
	std::deque<ITEM*> items;
	std::vector<char> collisions; // W == wall, H == hole, future implementaiton may have collision types class
	bool impasse_bool = false;
	
	COLLISIONS();
	COLLISIONS( ITEM* );
	~COLLISIONS();
	bool impasse(); // check if coordinate is traversable
	
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


// refactor this, it's so wonky
bool COLLISIONS::impasse()
{
	if ( impasse_bool ) return true;
	
	// if we dont find a 'W', return false. Is not an impasse
	if ( std::find_if( collisions.begin(), collisions.end(), []( char& c ){ return (c == 'W'); } ) == collisions.end() )
	{
		return false;
	}
	
	return true;
}

#endif
