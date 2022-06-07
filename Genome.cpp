#include "Genome.h"
#include "Randomize.h"

Gene ReadGenCode(string code, Param p) {
	Gene temp;
	SensorType st = END_S;
	ActionType at = END_A;
	
	string codeBin;
	for (char i : code) codeBin += HexDigitToBin(i);
	reverse(codeBin.begin(), codeBin.end());

	temp.input_type = codeBin[0] - 60; // Prebacivanje iz ASCII vrednosti u ceo broj.
	temp.input_type %= 2;
	temp.input = stoul(codeBin.substr(1, 7), nullptr, 2); // Konvertovanje binarne vrednosti u ceo broj
	if (temp.input_type == Sensor) temp.input %= st;
	else temp.input %= p.numberOfNeurons; //number of neurons

	temp.output_type = codeBin[8] - 60;
	temp.output_type %= 2;
	temp.output = stoul(codeBin.substr(9, 15), nullptr, 2);
	if (temp.output_type == Action) temp.output %= at;
	else temp.output %= p.numberOfNeurons; 

	float x = stoul(codeBin.substr(16, 31), nullptr, 2);
	temp.weight = x / 8192; // Dobijamo vrednost jacine veze od -4.0 do 4.0

	return temp;
}

void PrintGene(Gene g) {
	cout << g.input_type << ": " << g.input << endl;
	cout << g.output_type << ": " << g.output << endl;
	cout << "Weight: " << g.weight << endl << endl;
}

Genome operator+(const Genome& g1, const Genome& g2) {
	Genome gen = {};
	if (g1.size() != g2.size()) return gen;

	for (int i = 0; i < g1.size(); ++i) {
		int k = randomChance(0.5) % 2;
		if (k == 0) gen.push_back(g1[i]);
		if (k == 1) gen.push_back(g2[i]);
	}

	return gen;
}