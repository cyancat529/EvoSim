#ifndef Param_HEADER
#define Param_HEADER

#include <fstream>
#include <string>
#include <vector>

class Param {
public:
	int numberOfNeurons;
	int geneSize;
	int generationLength;
	int generationSize;
	bool mutation;
	float mutationChance;
	bool autorun;
	int autorunNumOfGen;
	int survivalCrit;
	int survivalRange;
};

Param InitParam(std::string fileName);


#endif