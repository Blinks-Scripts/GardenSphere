#ifndef LOCTEMP_H
#define LOCTEMP_H

#include <string>
#include <fstream>
#include "jfxlib.h"
#include "building.h"
#include "collisions.h"

typedef std::map<std::string,std::vector<std::pair<int,int>>> tile_data;
typedef std::map<std::pair<int,int>,COLLISIONS*> collisions_map;

class LOCATION {
	private:
		
		std::string tile_filename;
		JFXLIB* jfx_name_map;	
	    tile_data build_params; // <building nickname, vector of each location to make one of these buildings>
		
		
		void set_tile_filename( std::string file ) { tile_filename = file; }	
		void load_tile_data( std::string );
		void store_building( BUILDING* ); // Accessor for vector<BUILDING*> buildings
		void construct_buildings();
		void add_building_collisions( BUILDING* );
		bool destructor_flag_1 = false;
	

	public:
		LOCATION();
		LOCATION( std::string, JFXLIB* );
		~LOCATION();
		
		collisions_map collisions;
		std::vector<BUILDING*> buildings;
		void add_item( int, int, ITEM* );
		std::deque<ITEM*>* get_item_pile( int, int );
		bool collision_is_impasse( int, int );
		void draw_self();
		
		
};

LOCATION::LOCATION()
{
	jfx_name_map = new JFXLIB();
	destructor_flag_1 = true;
	set_tile_filename( "home.tile" );
	load_tile_data( tile_filename );
	construct_buildings();
}

LOCATION::LOCATION( std::string tile, JFXLIB* lib )
{
	std::cout << "location constructor\n";
	jfx_name_map = lib;
	set_tile_filename( tile );
	load_tile_data( tile_filename );
	construct_buildings();
}

LOCATION::~LOCATION()
{
	BUILDING* building_iter;
    // free memory of each building object for this LOCATION
    for ( auto iter : buildings ) {
        building_iter = iter;
        delete building_iter;
    }
    COLLISIONS* collisions_iter;
    for ( auto iter : collisions ) {
		collisions_iter = iter.second;
		delete collisions_iter;
	}
    if ( destructor_flag_1 ) delete jfx_name_map;
}

void LOCATION::load_tile_data( std::string filename )
{
	std::ifstream file(filename);
	
	// puts paramaters for buildings into build_params;
	while ( file.peek() != EOF ) {
		std::string building_nickname;
		std::string tempY, tempX;
		int tempY_int, tempX_int;

		// xxx.tile >> building_key, y, x
		file >> building_nickname >> tempY >> tempX;
		tempY_int = std::stoi( tempY );
		tempX_int = std::stoi( tempX );
		std::pair<int,int> building_coordinates= { tempY_int, tempX_int };

		// push the coordinates of the building into that building type's vector
		build_params[building_nickname].push_back(building_coordinates);

		// check the next character to see if we should stop reading
		char trail = file.get();
		while ( trail != '\n' ) trail = file.get(); // ignore newlines so get() can get a char or EOF
	}
	file.close(); // it's just good practice
}
void LOCATION::store_building( BUILDING* building )
{
	buildings.push_back( building );
}

void LOCATION::construct_buildings()
{
	// each entry in build_params will be a pair represent a building type
	// and a vector containing the coordinates at which to create instances of that building type
	for ( auto building_type : build_params ) {
		
		std::cout << "preparing nickname query \n";
		std::string building_filename = jfx_name_map->lookup( building_type.first ); // get the filename
		std::cout << "success: " << building_type.first << " is " << building_filename << "\n";

		// and for every stored coordinate of that building type, 
		// construct a new BUILDING object and store it
		for ( auto each_copy : building_type.second ) {
			//std::cout << "preparing to make a copy of " << building_type.first << "\n";
			int tempY = each_copy.first;
			int tempX = each_copy.second;
			//std::cout << "copy's coordinates extracted \n";
			// make a building and store the pointer in this LOCATION's buildings vector
			BUILDING* new_building = new BUILDING( building_filename, tempY, tempX );
			add_building_collisions( new_building );
			store_building( new_building );
		}
	}
}

void LOCATION::add_building_collisions( BUILDING* building )
{
	 int y = building->get_pY();
	 int x = building->get_pX();
	 int collision_y_offset;
	 int collision_x_offset;
	 int collision_height;
	 int collision_width;
	 
	 std::cout << "adding building collisions \n";
	 // for each <collision_param>collision box in this building's vector of collision boxes
	 for ( auto each_cb : building->collision_boxes ) {
		 
	 	 collision_y_offset = each_cb->getYOFF();
	 	 collision_x_offset = each_cb->getXOFF();
	 	 collision_height = each_cb->getH();
	 	 collision_width = each_cb->getW();
	 	 
		 for ( int i = collision_y_offset; i < collision_y_offset + collision_height; i++ ) {
			 for ( int k = collision_x_offset; k < collision_x_offset + collision_width; k++ ) {
				 std::pair<int,int> temp_pair = std::make_pair( (y+i), (x+k) );
				 collisions[temp_pair] = new COLLISIONS();
			 }
		 }
	 }
}

void LOCATION::add_item( int Y, int X, ITEM* item )
{
	std::pair<int,int> coordinates = std::make_pair( Y, X );
	if ( collisions[coordinates] != nullptr ) {
		collisions[coordinates]->add_item( item );
	} else {
		collisions[coordinates] = new COLLISIONS( item );
	}
}

std::deque<ITEM*>* LOCATION::get_item_pile( int Y, int X )
{
	std::pair<int,int> query = std::make_pair( Y, X );
	std::deque<ITEM*>* item_pile;
	
	auto it = collisions.find(query);
	if (it != collisions.end()) {
		// Collision exists, get the item pile
		item_pile = it->second->get_item_pile_pointer();
	} else {
		// Collision does not exist, create a new one
		COLLISIONS* new_collision = new COLLISIONS(new ITEM(" ", false));
		collisions.insert(std::make_pair(query, new_collision));
		item_pile = new_collision->get_item_pile_pointer();
	}
	
	return item_pile;
}

bool LOCATION::collision_is_impasse( int Y, int X )
{
	if ( Y < 0 || X < 0 ) return false;
	
	std::pair<int,int> coordinates = std::make_pair(Y, X);
	//std::cout << "seg fault? \n";
	if ( collisions[coordinates] ) {
		//std::cout << "breaks here \n";
		return collisions[coordinates]->impasse();
	} else {
		collisions[coordinates] = new COLLISIONS( new ITEM( " ", false ) );
		return collisions[coordinates]->impasse();
	}
	//std::cout << "seg fault still? \n";
	return false;
}

void LOCATION::draw_self()
{
	for ( auto each_building : buildings ) {
        each_building->draw_self();
    }
    //std::cout << "buildings drawn\n";
    int collision_Y;
    int collision_X;
    for ( auto each_collision : collisions ) {
		collision_Y = each_collision.first.first;
		collision_X = each_collision.first.second;
		//std::cerr << "collision Y: " << collision_Y << "   collision X: " << collision_X << "\n";
		each_collision.second->draw_self( collision_Y, collision_X );
	}
	
}
#endif
