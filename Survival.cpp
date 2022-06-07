#include "Survival.h"

bool survivalCriteriaWE(Coord c, int n) {
	if ((c.x <= n) || (c.x >= 100 - n)) return true;
	else return false;
}

bool survivalCriteriaNS(Coord c, int n) {
	if ((c.y <= n) || (c.y >= 100 - n)) return true;
	else return false;
}

bool survivalCriteriaCORN(Coord c, int n) {
	if (((c.x <= n) && (c.y <= n)) || ((c.x >= 100 - n) && (c.y <= n)) || ((c.x <= n) && (c.y >= 100 - n)) || ((c.x >= 100 - n) && (c.y >= 100 - n))) return true;
	else return false;
}

vector<Organism> naturalSelection(vector<Organism> vec, int n, int survivalCrit) {
	vector<Organism> temp;

	for (Organism o : vec) {
		if (survivalCrit == 0 && survivalCriteriaWE(o.coord, n)) {
			temp.push_back(o);
		}
		if (survivalCrit == 1 && survivalCriteriaNS(o.coord, n)) {
			temp.push_back(o);
		}
		if (survivalCrit == 2 && survivalCriteriaCORN(o.coord, n)) {
			temp.push_back(o);
		}
	}

	return temp;
}