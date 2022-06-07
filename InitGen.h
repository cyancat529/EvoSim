#ifndef InitGen_HEADER
#define InitGen_HEADER

#include "Survival.h"

extern float survivalRate;
vector<Organism> InitGen(vector<Organism> vecPrev, int genNum, int genSize, Param p);

#endif