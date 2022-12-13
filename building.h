#ifndef BUILDING_H
#define BUILDING_H


#include <fstream>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
#include <sstream>

class BUILDING {
    public:

        std::string name = "default building";
        std::vector<std::string> image;
        int height;
        int width;
        std::vector<std::pair<std::pair<int,int>,std::pair<int,int>>> collision_boxes;
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
    std::pair<int,int> col_hw;
    std::pair<int,int> tl_offset;
    
    std::string temp;
    std::string temp2;
    std::string temp3;
    
    std::ifstream builder( jfx_file );
    while ( builder.is_open() ) {
        std::cout << "building stois \n";
        getline( builder, name );
        std::cout << "current building name =" << name << "\n";
        getline( builder, temp );
        height = std::stoi( temp );
        getline( builder, temp );
        width = std::stoi( temp );        
  
		getline( builder, temp );
		while ( temp[0] != ':' ) {
			std::stringstream ss(temp);
			
			ss >> temp2 >> temp3;
			tl_offset.first = std::stoi( temp2 );
			tl_offset.second = std::stoi( temp3 );
			ss >> temp2 >> temp3;
			col_hw.first = std::stoi( temp2 );
			col_hw.second = std::stoi( temp3 );
			
			collision_boxes.push_back( std::make_pair( tl_offset, col_hw ) );
			getline( builder, temp );	
			
			/*
			 * while ( temp[0] != ':' ) {
			std::cout << "first temp = " << temp << "\n";
			tl_offset.first = std::stoi( temp );
			getline( builder, temp );
			tl_offset.second = std::stoi( temp );
			getline( builder, temp );
			col_hw.first = std::stoi( temp );
			getline( builder, temp );
			col_hw.second = std::stoi( temp );
			
			collision_boxes.push_back( std::make_pair( tl_offset, col_hw ) );
			getline( builder, temp );			
					*/
		}
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
