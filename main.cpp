/*#include <iostream>
#include <time.h>
#include <vector>

#include "SDL.h"
#include "Organism.h"
#include "Global.h"

#undef main

using namespace std;


int main() {
	vector<Organism> org;
	Organism temp;
	int x, y;
	
	Organism* grid[40][40] = {};

	for (int i = 0; i < 20; ++i) {
		srand(time(0));
		
		if (i == 0) {
			x = rand() % 40;
			y = rand() % 40;
			temp.coord.x = x;
			temp.coord.x = y;
			org.push_back(temp);
			grid[x][y] = &org.back();
		}
		else {
			cout << "pocetak" << endl;
			bool pass = false;
			while (!pass) {
				x = rand() % 40;
				y = rand() % 40;
				if (grid[x][y] == NULL) pass = true;
			}
			cout << "kraj" << endl;
			temp.coord.x = x;
			temp.coord.x = y;
			org.push_back(temp);
			grid[x][y] = &org.back();
		}
	}

	return 0;
}*/