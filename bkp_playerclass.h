#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H

#include <utility>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

class PLAYER {
    public:
        std::pair<int,int> pos; // y, x
        std::string name = "default";
        char pl_symbol = 'o';
        int step_count = 0;
       

        PLAYER();
        PLAYER( std::pair<int,int> );
        ~PLAYER();

        void print_pos();
        void ch_name( std::string& );
        void incr_step();
        void incr_step( size_t n );
        const char* get_step_str();

};

PLAYER::PLAYER()
{
    pos = {0,0};
}

PLAYER::PLAYER( std::pair<int,int> p )
{
    pos = p;
}

PLAYER::~PLAYER()
{
    std::cout << "player destructor\n";
    return;
}

void PLAYER::ch_name( std::string& n )
{
    name = n;
}

void PLAYER::print_pos() {
    std::cout << name << " y = " << pos.first << std::endl;
    std::cout << std::string(this->name.length(), ' ') << " x = " << pos.second << std::endl;
}

void PLAYER::incr_step() {
    step_count += 1;
}

void PLAYER::incr_step( size_t n ) 
{
    step_count += n;
}

const char* PLAYER::get_step_str()
{
    std::string step_str = std::to_string( step_count );
    return step_str.c_str();
}

#endif
