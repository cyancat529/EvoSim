#ifndef Global_HEADER
#define Global_HEADER

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

enum Dir {N,NE,E,SE,S,SW,W,NW};

struct Coord {
	int x;
	int y;
};


string HexDigitToBin(char h);

/*int StrToHex(std::string str) {
	unsigned int i;
	std::istringstream iss(str);
	iss >> std::hex >> i;
	return i;
}*/

#endif

