#ifndef BUILDINH_H
#define BUILDING_H


#include <fstream>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <ncurses>

class BUILDING {
    std::string name = "default building";
    std::vector<std::string> image;

    BUILDING();
    //BUILDING( std::string filename );
    ~BUILDING();
    WINDOW* draw_self( WINDOW* hostWindow = stdscr, int posY = 1, int posX = 1 );

};

BUILDING::BUILDING() {
    std::string temp;
    ifstream builder( "defaultbuilding.jfx" );
    while ( builder.is_open() ) {
        getline( builder, name );
        while ( getline( builder, temp ) ) {
            image.push_back( temp );
        }
    }    
}

WINDOW* BUILDING::draw_self( WINDOW* hostWindow, int posY, int posX )
{
    int i = 0;
    while ( i < image.size() )
    {
        mvaddstr( posY, posX, image[i++].c_str();
        posY++;
    }
}
