#ifndef POSITION_H
#define POSITION_H

#include "worldmap.h"
#include "location.h"

class POSITION {
	public:
		POSITION() { std::cout << "position constructed \n"; }
		POSITION( int Y, int X ) { setPY(Y); setPX(X); _update(); }
		~POSITION();

		WORLD_MAP* world_map = new WORLD_MAP();
		LOCATION* location;	

		int getPY() { return pY; }    
		int getPX() { return pX; }        
		
		int getWY() { return wY; }    
		int getWX() { return wX; }
    
    private:
		int pY = 0;
		int pX = 0; // Coordinates on screen ( within tile )
		int wY = 0;
		int wX = 0; // Coordinates of map tile ( within world map )
		
		void setPY(int y) { pY = y; }
		void setPX(int x) { pX = x; }
		void setWY(int y) { wY = y; }
		void setWX(int x) { wX = x; }
		void incrWYX( int y, int x ) { wY += y; wX += x; _update(); }
		
		void set_world_map( WORLD_MAP* WM ) { world_map = WM; }
		
		friend class PLAYER;
    
	
		void _update();
};

POSITION::~POSITION() {
	delete world_map;
	world_map = NULL;
}

void POSITION::_update()
{
	std::pair<int,int> tile_request = std::make_pair( wY, wX );
	location = world_map->get_location( tile_request );
}





#endif
