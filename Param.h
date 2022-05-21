#ifndef Param_HEADER
#define Param_HEADER

#include <fstream>

const int numberOfNeurons = 4;
const int geneSize = 16;
const int generationLength = 300;
const int generationSize = 500;

struct Parameters {
	int populationSize;
	int numberOfGenerations;
};



#endif