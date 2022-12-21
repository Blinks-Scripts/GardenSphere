#include <string>

// Default screen dimensions
const int BOARDHEIGHT = 30;
const int BOARDWIDTH = 60;
const int BORDERTOP = 1;
const int BORDERLEFT = 5;
const int BORDERBOTTOM = BORDERTOP + BOARDHEIGHT;
const int BORDERRIGHT = BORDERLEFT + BOARDWIDTH;

// Default Player coordinates
const int DEFAULT_PY = 20;
const int DEFAULT_PX = 40;

// Default HUD position and size
const int HUDY = 10;
const int HUDX = 70;
const int HUDH = 20;
const int HUDW = 20;

// Default World Size
const int WORLDTOP = 0;
const int WORLDLEFT = 0;
const int WORLDBOTTOM = 8;
const int WORLDRIGHT = 8;

const std::string DEFAULT_PLAYER_SPRITES = "player.jfx";

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT 
};
