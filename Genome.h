#ifndef Genome_HEADER
#define Genome_HEADER

#include "Global.h"
#include <string>

using namespace std;

// Gen je zaprvo veza �ula i neurona ili neurona i akcije.
// Svaka veza ima i svoju te�inu koja odre�uje ishod izvr�avanje odre�ene radnje.

struct Gene {
	short int input_type;  // Culo / neuron
	short int input;
	short int output_type;  // Neuron / akcija
	short int output;
	int weight;  
};

typedef vector<Gene> Genome;

Gene ReadGenCode(string code);

#endif