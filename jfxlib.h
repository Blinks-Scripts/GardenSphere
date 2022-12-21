#ifndef JFXLIB_H
#define JFXLIB_H

#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <iostream>

class JFXLIB {

    public:
        // translate a building nnickame to its associated filename
        std::map<std::string,std::string> table; // first == building nickname (at top of .jfx file) ( DefBld )
											     // second == *IS* a .jfx filename std::string ( defaultbuild.jfx )
        
        JFXLIB(); // constructor
        std::string lookup( std::string ); // Return filename of a given building nickname

};

/**
 * Default Constructor
 * 
 * Load the definitions file into
 * this library's table
 ***/
JFXLIB::JFXLIB() {

    std::ifstream lib_file( "jfxlibdefs.h" );
    while ( lib_file.is_open() ) {

        while ( lib_file.peek() != EOF ) {
            std::string key;
            std::string file_string;
            lib_file >> key >> file_string;
            table[key] = file_string;
        }

        lib_file.close();
    }

}

/**
 * return the filename associated
 * with the building nickname passed as
 * a key
 ***/
std::string JFXLIB::lookup( std::string key ) 
{
	std::cout << "looking up: " << key << "\n";
    return table[key];
}


#endif
