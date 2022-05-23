#include "Survival.h"

bool survivalCriteriaWE(Coord c, int n) {
	if ((c.x <= n) || (c.x >= 100 - n)) return true;
	else return false;
}

vector<Organism> naturalSelection(vector<Organism> vec, int n) {
	vector<Organism> temp;

	for (Organism o : vec) {
		if (survivalCriteriaWE(o.coord, n)) {
			temp.push_back(o);
		}
	}

	return temp;
}