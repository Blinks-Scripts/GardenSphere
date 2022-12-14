#ifndef LOCATION_H
#define LOCATION_H

#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "building.h"
#include "jfxlib.h"
#include "collisions.h"
#include "item.h"


class LOCATION {
    public:
        std::string filename; // name of file containing specifications of a LOCATION tile
        //std::vector<std::vector<int>> collision_map;
        std::vector<BUILDING*> bldngs; // vector of the buildings for this LOCATION
        
        std::map<std::pair<int,int>, COLLISIONS*> collisions;
		

        LOCATION(); // Default Constructor, constructs home tile
        LOCATION( std::string, JFXLIB* ); // Construct the location given using the given library
        ~LOCATION(); // Destructor
        void add_bldng_collisions( BUILDING* );
        void draw_self(); // Using the ncurses, draw this LOCATION's graphics to screen
        void add_item_collision( std::pair<int,int>, ITEM* );
};

/*
 * see the custom constructor for more details
 */
LOCATION::LOCATION()
{
    filename = "home.tile";
    std::ifstream file( filename );
    while ( file.is_open() ) {
        
        // hold the info on building files to read
        std::map<std::string,std::vector<std::pair<int,int>>> build_params;

        // puts paramaters for buildings into build_params;
        while ( file.peek() != EOF ) {
            std::string temp_filekey; //nickname of building
            std::string tempY, tempX; // position to draw the building
            int tempYint, tempXint; // integer conversion of position

            file >> temp_filekey >> tempY >> tempX;
            std::cout << " first set of stois \n";
            tempYint = std::stoi( tempY );
            tempXint = std::stoi( tempX );

            //build_params[temp_filekey] = std::vector<std::pair<int,int>>();
            build_params[temp_filekey].push_back(std::make_pair( tempYint, tempXint ));
            char trail = file.get();
            if( trail == ':' ) break;
            while ( trail != '\n' ) trail = file.get();
        }
        file.close();

        // grab building file reference strings and construct each building
        for ( auto kv_pair : build_params )
        {
            std::string temp_filestr = "defaultbuilding.jfx"; // default file name

            for ( auto each_copy : kv_pair.second ) {
                BUILDING* n_bld = new BUILDING( temp_filestr, each_copy.first, each_copy.second );
                std::cout << "n_bld y = " << n_bld->position.first << std::endl;
                std::cout << "b_bld x = " << n_bld->position.second << std::endl;
                
                add_bldng_collisions( n_bld );
                
                bldngs.push_back(n_bld);
            }
        }
    }
}

LOCATION::LOCATION( std::string tile_file, JFXLIB* lib )
{
    filename = tile_file;
    std::ifstream file( filename );

    while ( file.is_open() ) {
        
        // hold the info on building files to read
        std::map<std::string,std::vector<std::pair<int,int>>> build_params;

        /*
         * First collect the info on all buildings for this LOCATION tile
         * We use the ifstream to feed building nickname into temp_filekey
         *                             building position into tempY, tempX
         *
         * After all necessary buildings are read from the .tile file, go ahead
         * and construct each one. Buildings are read from .tile and constructed
         * separately because the BUILDING constructor must open a file.
         *
         * Side-chained map (build_params) used to store duplicate buildings appearing
         * in multiple locations
         * */

        // puts paramaters for buildings into build_params;
        while ( file.peek() != EOF ) {
            std::string temp_filekey; //
            std::string tempY, tempX;
            int tempYint, tempXint;

            // xxx.tile >> building_key, y, x
            file >> temp_filekey >> tempY >> tempX;
            std::cout << " first set of stois \n";
            tempYint = std::stoi( tempY );
            tempXint = std::stoi( tempX );

            // push the coordinates of the building into that building type's vector
            build_params[temp_filekey].push_back(std::make_pair( tempYint, tempXint ));

            // check the next character to see if we
            // should stop reading
            char trail = file.get();
            if( trail == ':' ) break; // custom delimiter, for future application
            while ( trail != '\n' ) trail = file.get(); // ignore newlines so get() can get a string or EOF
        }
        file.close(); // it's just good practice

        // grab building file reference strings and construct each building
        // build_params.first == blding nickname found in .jfx file
        // build_params.second == <pair> coordinates
        
        // for each entry in build_params
        for ( auto kv_pair : build_params )
        {
            
            std::string temp_filestr = lib->lookup( kv_pair.first );

            // and for every coordinate pair in that entry's vector
            for ( auto each_copy : kv_pair.second ) {
                // make a building and store the pointer in this LOCATION's bldngs
                BUILDING* n_bld = new BUILDING( temp_filestr, each_copy.first, each_copy.second );
                std::cout << "n_bld y = " << n_bld->position.first << std::endl;
                std::cout << "b_bld x = " << n_bld->position.second << std::endl;
                
                add_bldng_collisions( n_bld );
                
                bldngs.push_back(n_bld);
            }
        }
    }
}

/**
 * destructor
 **/
LOCATION::~LOCATION() {
    BUILDING* b;
    // free memory of each building object for this LOCATION
    for ( auto iter : bldngs ) {
        b = iter;
        delete b;
    }
        
}
        
/**
 * instantiate COLLISIONS for all the walls of the
 * buiilding using default COLLISION
 ************************************/
 void LOCATION::add_bldng_collisions( BUILDING* b )
 {
	 int y = b->position.first;
	 int x = b->position.second;
	 
	 std::pair<std::pair<int,int>,std::pair<int,int>> col_b; // collision box temp 
	 
	 for ( auto each_b : b->collision_boxes ) {
	 	 
		 for ( int i = each_b.first.first ; i < each_b.first.first + each_b.second.first; i++ ) {
			 for ( int k = each_b.first.second; k < each_b.first.second + each_b.second.second; k++ ) {
				 std::pair<int,int> temp_pair = std::make_pair( (y+i), (x+k) );
				 collisions[temp_pair] = new COLLISIONS();
			 }
		 }
	 }
 }
 
 /**
  * instantiate a COLLISION if needed and add an
  * item to the COLLISION object's item vector
  *******/
  void LOCATION::add_item_collision( std::pair<int,int> pos, ITEM* itm )
  {
	  if( collisions[pos] == nullptr ) {
		  collisions[pos] = new COLLISIONS( itm );
	  } else if ( itm->itm_symbol != ' ' ) {
		  if ( itm->impasse ) collisions[pos]->impasse_bool=true;
	      collisions[pos]->items.push_back( itm );
	  }
	  
  }
        
/**
 * draw this LOCATION to the stdscr
 **/
void LOCATION::draw_self()
{
	/*
     * tell each building in this location
     * to draw itself
     * */
    for ( auto b : bldngs ) {
        b->draw_self();
    }
    for ( auto i : collisions ) {
		if ( i.second->collisions.empty() && ! i.second->items.empty() ) {
			mvaddch( i.first.first, i.first.second, i.second->items.front()->itm_symbol );
		}
	}

}



#endif
