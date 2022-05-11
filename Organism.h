#ifndef Organism_HEADER
#define Organism_HEADER

#include "Global.h"

struct Coord {
	int x;
	int y;
};

class Organism {
public:
	bool alive;
	Coord coord;
	int priority;
};

#endif