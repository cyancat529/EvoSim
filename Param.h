#ifndef Param_HEADER
#define Param_HEADER

#include <fstream>

const int numberOfNeurons = 8;
const int geneSize = 32;
const int generationLength = 300;
const int generationSize = 500;
const bool mutation = true;
const float mutationChance = 0.001;
extern bool autorun;
const int autorunNumOfGen = 100;

struct Parameters {
	int populationSize;
	int numberOfGenerations;
};




#endif