#include "Genome.h"

Gene ReadGenCode(string code) {
	Gene temp;
	int codeInt = std::stoul(code, nullptr, 16);
	string codeBin;
	for (char i : code) codeBin += HexDigitToBin(i);
	reverse(codeBin.begin(), codeBin.end());
	temp.input_type = codeBin[0] - 60; // Prebacivanje iz ASCII vrednosti u ceo broj.
	temp.input = stoi(codeBin.substr(1, 7), nullptr, 2); // Konvertovanje binarne vrednosti u ceo broj
	temp.output_type = codeBin[8] - 60;
	temp.output = stoi(codeBin.substr(9, 15), nullptr, 2);
	temp.weight = stoi(codeBin.substr(16, 31), nullptr, 2);
	return temp;
}