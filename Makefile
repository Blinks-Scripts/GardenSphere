CXXFLAGS+=-std=c++11 -Wall -Wextra -Werror -pedantic -I.

all: gardengame

gardengame: main.cxx timer.h gameclass.h constants.h location.h playerclass.h position.h building.h worldmap.h collisions.h jfxlib.h
	g++ $(CXXFLAGS) -o gardengame main.cxx timer.h gameclass.h constants.h location.h playerclass.h position.h building.h worldmap.h collisions.h jfxlib.h -lncurses

clean:
	rm -f *.o

