#ifndef Survival_HEADER
#define Survival_HEADER

#include "Organism.h"

bool survivalCriteriaWE(Coord c, int n);
bool survivalCriteriaNS(Coord c, int n);
bool survivalCriteriaCORN(Coord c, int n);

vector<Organism> naturalSelection(vector<Organism> vec, int n, int survivalCrit);


#endif 

