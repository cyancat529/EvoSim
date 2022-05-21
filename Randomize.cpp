#include "Randomize.h"
#include "Param.h"

bool randomChance(float f) {
	if (f <= 0) return false;
	else {
		return (std::rand() % 100) < (f * 100);
	}
}

std::string randomGenCode() {
	std::string s = "";
	for (int i = 0; i < geneSize*8; ++i) {
		int x = rand()%16;
        switch (x) {
        case 0: s += "0"; break;
        case 1: s += "1"; break;
        case 2: s += "2"; break;
        case 3: s += "3"; break;
        case 4: s += "4"; break;
        case 5: s += "5"; break;
        case 6: s += "6"; break;
        case 7: s += "7"; break;
        case 8: s += "8"; break;
        case 9: s += "9"; break;
        case 10: s += "A"; break;
        case 11: s += "B"; break;
        case 12: s += "C"; break;
        case 13: s += "D"; break;
        case 14: s += "E"; break;
        case 15: s += "F"; break;
        }
	}
    return s;
}
