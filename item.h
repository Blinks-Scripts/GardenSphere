#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "timer.h"

class ITEM {

	public:
	char itm_symbol;
	std::string item_name;
	bool impasse = false;
	TIMER* timer = new TIMER();
	
	ITEM();
	ITEM( std::string, bool );
	~ITEM();
	bool operator==( ITEM* );

};

ITEM::ITEM()
{}

ITEM::ITEM( std::string name, bool impas ) : itm_symbol(name[0]), item_name(name), impasse(impas) {}

ITEM::~ITEM() {}

bool ITEM::operator==( ITEM* rh ) {
	return ( this->item_name == rh->item_name );
}

#endif
