#ifndef Global_HEADER
#define Global_HEADER

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const char hexDigits[16] = { '0','1','2','3' ,'4' ,'5' ,'6' ,'7' ,'8' ,'9' ,'A' ,'B' ,'C' ,'D' ,'E', 'F' };
extern int generationNumber;

enum Dir {N,NE,E,SE,S,SW,W,NW};

struct Coord {
	int x;
	int y;
};

string HexDigitToBin(char h);

#endif

