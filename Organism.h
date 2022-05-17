#ifndef Organism_HEADER
#define Organism_HEADER

#include "Global.h"
#include "Genome.h"

class Organism {
public:
	bool alive;
	Coord coord;
	int priority;
	uint16_t food;
};

#endif