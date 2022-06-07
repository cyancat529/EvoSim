#ifndef Genome_HEADER
#define Genome_HEADER

#include "Global.h"
#include "Neuron.h"
#include "Param.h"

#include <string>

using namespace std;

// Gen je zaprvo veza èula i neurona ili neurona i akcije.
// Svaka veza ima i svoju težinu koja odreðuje ishod izvršavanje odreðene radnje.

const int Sensor = 1; // Cula su uvek ulaz. 
const int Action = 1; // Akcije su uvek izlaz. 
const int Neuron = 0; // Neuroni mogu biti i ulaz i izlaz.

struct Gene {
	string code;
	unsigned short int input_type;  // Culo / neuron
	unsigned short int input;
	unsigned short int output_type;  // Neuron / akcija
	unsigned short int output;
	float weight;  
};

typedef vector<Gene> Genome;
Genome operator+(const Genome& g1, const Genome& g2);

Gene ReadGenCode(string code, Param p);
void PrintGene(Gene g);


#endif