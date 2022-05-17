#ifndef Neuron_HEADER
#define Neuron_HEADER

//

enum SensorType {
	X_POS,  //X pozicija organizma
	Y_POS,	//Y pozicija organizma
	EDGE_DIST_X,   //X razdaljina od zapadne ivice
	EDGE_DIST_Y,   //Y razdaljina od severne ivice
	EDGE_DIST,   //Razdaljina od najblize ivice
	FOOD_X,	  //X razdaljina od najblize hrane
	FOOD_Y,	  //Y razdaljina od najblize hrane
	FOOD_IN_RAD,   //Hrana u odredjenoj razdaljini
	POPULATION_DENSITY,   //Gustina naseljenosti u odredjenoj razdaljini
	AGE,  //Broj koraka od pocetka generacije
	FOOD_COUNT,  //Broj sakupljene hrane
};

enum ActionType {
	MOVE_X,
	MOVE_Y,
	MOVE_FW,
	MOVE_N,
	MOVE_W,
	MOVE_S,
	MOVE_E,
};

#endif
