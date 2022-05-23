#include "InitGen.h"

vector<Organism> InitGen(vector<Organism> vecPrev, int genNum, int genSize) {
	memset(grid, 0, sizeof(grid));

	vector<Organism> vecSurv;
	vector<Organism> vecNewGen;
	vecSurv = naturalSelection(vecPrev, 15);
	int tempSize = vecSurv.size();
	cout << "Generation " << genNum - 1 << " survival rate: " << float(tempSize) / float(genSize) * 100 << "%" << endl;

	for (int i = 0; i < genSize; ++i) {
		int i1 = rand() % tempSize;
		int i2 = i1;
		int x, y;
		while (i2 == i1) i2 = rand() % tempSize;
		Organism temp;
		temp.genCode = vecSurv[i1] + vecSurv[i2];
		temp.Init();

		if (i == 0) {
			x = rand() % 100;
			y = rand() % 100;
			temp.coord.x = x;
			temp.coord.y = y;
			temp.lastCoord.x = x;
			temp.lastCoord.y = y;
			temp.id = i + 1;
			vecNewGen.push_back(temp);
			grid[x][y] = i + 1;
		}
		else {
			bool pass = false;
			while (!pass) {
				x = rand() % 100;
				y = rand() % 100;
				if (grid[x][y] == 0) pass = true;
			}
			temp.coord.x = x;
			temp.coord.y = y;
			temp.lastCoord.x = x;
			temp.lastCoord.y = y;
			temp.id = i + 1;
			vecNewGen.push_back(temp);
			grid[x][y] = i + 1;
		}
	}

	return vecNewGen;
}

