#ifndef BUILDING_H
#define BUILDING_H


#include <fstream>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>

class BUILDING {
    public:

        std::string name = "default building";
        std::vector<std::string> image;
        int height;
        int width;
        std::pair<int,int> position;

        BUILDING();
        BUILDING( std::string jfx_file, int pY, int pX );
        ~BUILDING();
        WINDOW* draw_self( WINDOW* hostWindow = stdscr );

};

BUILDING::BUILDING() {
    position = std::make_pair( 1, 1 );
    std::string temp;
    std::ifstream builder( "defaultbuilding.jfx" );
    while ( builder.is_open() ) {
        getline( builder, name );
        getline( builder, temp );
        height = std::stoi( temp );
        getline( builder, temp );
        width = std::stoi( temp );
        while ( getline( builder, temp ) ) {
            image.push_back( temp );
        }
        builder.close();
    }    
}

BUILDING::BUILDING( std::string jfx_file, int pY, int pX ) {
    position.first = pY;
    position.second = pX;
    std::string temp;
    std::ifstream builder( jfx_file );
    while ( builder.is_open() ) {
        std::cout << "building stois \n";
        getline( builder, name );
        getline( builder, temp );
        height = std::stoi( temp );
        getline( builder, temp );
        width = std::stoi( temp );
        std::cout << "constructing << " << name << std::endl;
        while ( getline( builder, temp ) ) {
            image.push_back( temp );
        }
        builder.close();
    }    
}

BUILDING::~BUILDING() 
{}

WINDOW* BUILDING::draw_self( WINDOW* hostWindow )
{
    size_t i = 0;
    int y = 0;
    while ( i < image.size() )
    {
        mvaddstr( (position.first + y), position.second, image[i++].c_str() );
        y++;
        
    }

    return hostWindow;
}

#endif
