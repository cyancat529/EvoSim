#ifndef Neuron_HEADER
#define Neuron_HEADER

#include "Global.h"

enum SensorType {
	X_POS,  // X pozicija organizma
	Y_POS,	// Y pozicija organizma
	DIST_FROM_CORNER, //  Razdaljina od (0,0) koordinate
	DIST_FROM_CENTER, //  Razdaljina od (0,0) koordinate
	EDGE_DIST,   // Razdaljina od najblize ivice
	OSCILATOR,  // Bioloski oscilator
	FOOD_IN_RAD,   // Hrana u odredjenoj razdaljini
	POPULATION_DENSITY,   // Gustina naseljenosti u odredjenoj razdaljini
	AGE,  // Broj koraka od pocetka generacije
	END_S   // Kraj liste senzora
};

enum ActionType {
	MOVE_FW,
	MOVE_N,
	MOVE_W,
	MOVE_S,
	MOVE_E,
	END_A
};



#endif
