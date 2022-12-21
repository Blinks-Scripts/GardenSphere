#ifndef BUILDING_H
#define BUILDING_H


#include <fstream>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
#include <sstream>
#include "timer.h"

class collision_param {
	public:
	int y_offset;
	int x_offset;
	int h;
	int w;
	
	void chW(int W) { w = W; }
	int getW() { return w; }
	void chH(int H) { h = H; }
	int getH() { return h; }
	void chXOFF(int X) { x_offset = X; }
	int getXOFF() { return x_offset; }
	void chYOFF(int Y) { y_offset = Y; }
	int getYOFF() { return y_offset; }
	
	
	friend class BUILDING;

	collision_param( int YOFF, int XOFF, int H, int W ) : y_offset(YOFF), x_offset(XOFF), h(H), w(W) {}
};

class BUILDING {
    private:
        std::string name = "default building";       
        
        int height;
        int width;
        int pY;
        int pX;
        
        std::vector<std::vector<std::string>> bldng_sprites;
        std::vector<std::string>* image;
        int image_frame_count = 1;
        std::vector<collision_param*> collision_boxes;
        TIMER* timer = new TIMER();
        
        int parse_stoi( std::ifstream&);
        void parse_collisions(std::ifstream&);
        void parse_image_frames(std::ifstream&);
        bool parse_building(std::string);
        
        friend class LOCATION;

	public:
        BUILDING();
        BUILDING( std::string jfx_file, int pY, int pX );
        ~BUILDING();
        
        void draw_self();
        
        int get_height() { return height; }
        int get_width() { return width; }
        int get_pY() { return pY; }
        int get_pX() { return pX; }
        void set_height( int H ) { height = H; }
        void set_width( int W ) { width = W; }
        void set_pY( int Y ) { pY = Y; }
        void set_pX( int X ) { pX = X; }

};

BUILDING::BUILDING() {
	pY = 25;
	pX = 40;
	bldng_sprites.resize(4);
	image = &bldng_sprites[0];
	
	parse_building("defaultbuilding.jfx");    
}

BUILDING::BUILDING( std::string jfx_file, int Y, int X ) {
	pY = Y;
	pX = X;
    bldng_sprites.resize(4);
	image = &bldng_sprites[0];
	parse_building( jfx_file );
}

BUILDING::~BUILDING()
{
	collision_param* del;
	for ( auto i : collision_boxes ) {
		del = i;
		delete del;
	}
	delete timer;
}

int BUILDING::parse_stoi( std::ifstream& ifs ) {
	std::string temp;
	getline( ifs, temp );
	int n = std::stoi( temp );
	return n;
}

void BUILDING::parse_collisions(std::ifstream& ifs) {
    std::string height, width, y_offset, x_offset; // tmeporary strings
    std::string line; // temp
    std::getline(ifs, line); // read a record from file into line
    std::cout << line << "\n";
    
    std::stringstream ss(line); // make a string stream from the line
   
    while (ss >> y_offset >> x_offset >> height >> width ) {
		// create a new set of collision box parameters
        collision_param* c_box;
        c_box = new collision_param(
            std::stoi(y_offset), std::stoi(x_offset), std::stoi(height), std::stoi(width) 
        );
        // add this collision box to the collection of collision boxes for this building
        collision_boxes.push_back(c_box);
    }
    
    // make sure a colon delimiter has been reached
    std::getline(ifs, line);
    if (line != ":") {
        std::exit(EXIT_FAILURE);
    }
    std::cout << "parsed collisions: current line is >>" << line << "\n";
}

void BUILDING::parse_image_frames( std::ifstream& ifs ) {
	std::string temp;
	// Get image delimited by ':'
	while ( getline( ifs, temp ) ) {
		// delimiter indicates end of image frame
		if ( temp == ":" ) {
			//bldng_sprites.resize( bldng_sprites.size()+1 );
			image += 1;
			image_frame_count += 1;
			continue;
		}
		// add the line to the image frame pointed to
		image->push_back( temp );
	}
}

bool BUILDING::parse_building( std::string filename ) 
{
	std::ifstream ifs( filename );
	while ( ifs.is_open() ) {
		getline( ifs, name );       // .jfx line 1 == name
		height = parse_stoi( ifs ); // .jfx line 2 == height
		width = parse_stoi( ifs );  // .jfx line 3 == width
		parse_collisions( ifs );    // .jfx line 4 == collisions (1 string containing 4 * n numbers)
		parse_image_frames( ifs );  // remainder of file is image frames delimited with a colon ":"
		
		ifs.close();
	}
	
	return true;
}

void BUILDING::draw_self()
{
    size_t y = 0;
    timer->update();
    int current_frame = (int)(timer->get_elapsed_int()) % image_frame_count;
    
    image = &bldng_sprites[current_frame];
    for (size_t  i = 0; i < image->size(); i++ )
    {
        mvaddstr( (pY + y), pX, image->at(i).c_str() );
        y++;        
    }
}
	
#endif
