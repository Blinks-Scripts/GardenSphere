CXXFLAGS+=-std=c++11 -Wall -Wextra -Werror -pedantic -I.

all: gardengame

gardengame: main.cxx building.h clock.h gameclass.h jfxlib.h location.h playerclass.h worldmap.h
	g++ $(CXXFLAGS) -o gardengame main.cxx building.h clock.h gameclass.h jfxlib.h location.h playerclass.h worldmap.h -lncurses

clean:
	rm -f *.o

