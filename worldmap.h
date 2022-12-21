#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <cstdlib>
#include <vector>
#include <string>
#include "jfxlib.h"
#include "location.h"

class WORLD_MAP {
    public:
        WORLD_MAP(); // Constructor
        ~WORLD_MAP(); // Destructor
        JFXLIB* graphics_lib = new JFXLIB(); // default constructor uses default graphics library
        
        /*
         * tile_array is the entire geographical game area,
         * where [0][0] is the top left corner of the map 
         * and [0][n] is top right corner. Each element will hold
         * the filename of its associated .tile file ( which contains
         * the information to construct the tile )
         * 
         * */
        std::vector<std::vector<std::string>> tile_array = { { "home.tile", "away.tile"} , { "away.tile", "home.tile" } };
		/*
		 * The WORLD_MAP reference container!
		 * Each LOCATION object pointer stored with
		 * coordinate std::pair as the key
		 **/
        std::map<std::pair<int,int>, LOCATION* > tile_table;

        // Accessors
        LOCATION* get_location( std::pair<int,int> );
};

/**
 * Default constructor
 * 
 * Constructs all the LOCATION objects necessary for
 * the game world and stores pointers to the objects in
 * and array representing the "map of the game"
 * **/
WORLD_MAP::WORLD_MAP() {
	std::cout << "world map constructor \n";
    int world_tile_y = 0;
    int world_tile_x = 0;
    int world_height = int(tile_array.size());
    int world_width = int(tile_array[world_tile_y].size());
    
    for ( world_tile_y = 0 ; world_tile_y < world_height; world_tile_y++ )
    {
        for ( world_tile_x = 0; world_tile_x < world_width; world_tile_x++ ) {
            LOCATION* n_loc = new LOCATION( tile_array[world_tile_y][world_tile_x], graphics_lib );
            tile_table[(std::make_pair(world_tile_y,world_tile_x))] = n_loc;
        }
		world_width = int(tile_array[world_tile_y].size());
    }
}

/**
 * Destructor
 * Frees memory of all LOCATION objects created
 * Frees memory of JFXLIBRARY object
 **/
WORLD_MAP::~WORLD_MAP() {
	// free the memory of each LOCATION
    for ( auto i : tile_table ) {
        delete i.second;
    }

    // free the memory of the graphics_lib
    delete graphics_lib;
}

/**
 * retrieve and return a pointer to the 
 * LOCATION object at the requested coordinates
 * 
 * @param tile_request A std::pair representing the y,x
 *                     coordinates of the LOCATION* to retrieve
 * @return <LOCATION*> A pointer to the location object requested
 * */
LOCATION* WORLD_MAP::get_location( std::pair<int, int> tile_request )
{
	if ( tile_table[tile_request] == nullptr ) {
		std::cerr << "WORLD_MAP::get_location(<" << tile_request.first << ", " << tile_request.second << ">) : Bad tile_request. Returning nullptr\n";
		return nullptr;
	}
    return tile_table[tile_request];
}

#endif
