#ifndef Organism_HEADER
#define Organism_HEADER

#include "Global.h"
#include "Genome.h"
#include "Randomize.h"
#include <algorithm> 
#include <utility> 
#include <math.h> 

extern int grid[100][100];

class Organism {
public:
	int id;
	int age;  // Starost (u koracima)
	string genCode;
	bool alive;
	Coord coord;
	Coord lastCoord;
	int priority;
	unsigned int food;
	Genome genome;
	bool activeSensorsB[END_S] = {};
	bool activeActionsB[END_A] = {};
	vector<unsigned short> activeSensors;  // Lista aktivnih cula
	vector<unsigned short> activeActions;  // Lista aktivnih akcija
	bool activeNeurons[numberOfNeurons] = {};  // Lista aktivnosti neurona
	float sensorInput[END_S] = {};
	float neuronInput[numberOfNeurons] = {};

	vector<unsigned short> neuronInputs[numberOfNeurons];
	vector<unsigned short> neuronInputW[numberOfNeurons];
	float neuronInputValue[numberOfNeurons];
	float neuronOutputValue[numberOfNeurons];

	vector<unsigned short> actionInputs[END_A];
	vector<unsigned short> actionInputW[END_A];
	float actionInputValue[END_A] = {};
	float actionOutputValue[END_A] = {};

	vector<unsigned short> directConn[END_A];
	vector<unsigned short> directConnW[END_A];

	void InitGenome() {
		for (int i = 0; i < geneSize; ++i) {
			Gene tempGen;
			string tempCode = genCode.substr(8 * i, 8);
			tempGen = ReadGenCode(tempCode);
			genome.push_back(tempGen);
		}
	}

	void PrintGenome() {
		for (Gene g : genome) {
			PrintGene(g);
		}
	}

	// Cula
	float SensorXPos(Coord c) {
		return float(c.x) / 100;
	}
	float SensorYPos(Coord c) {
		return float(c.y) / 100;
	}
	float SensorDistCorner(Coord c) {
		return hypot(c.x, c.y) / hypot(100,100);
	}
	float SensorDistCenter(Coord c) {
		return hypot(c.x - 50, c.y - 50) / hypot(50, 50);
	}
	float SensorEDist(Coord c) {
		return std::min(std::min(c.x, 100 - c.x), std::min(c.y, 100 - c.y)) / 50;
	}
	float SensorFoodRad(Coord c, int rad) {
		float counter = 0;
		for (int x = std::max(c.x - rad, 0); x < std::min(c.x + rad, 99); ++x) {
			for (int y = std::max(c.y - rad, 0); y < std::min(c.y + rad, 99); ++y) {
				if (grid[x][y] == -1) counter++;
			}
		}
		return counter / (rad * rad);
	};
	float SensorPopDensity(Coord c, int rad) {
		float counter = 0;
		for (int x = std::max(c.x - rad, 0); x < std::min(c.x + rad, 99); ++x) {
			for (int y = std::max(c.y - rad, 0); y < std::min(c.y + rad, 99); ++y) {
				if (grid[x][y] > 0) counter++;
			}
		}
		return counter / (rad * rad);
	}
	float SensorOscilator() {
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		return abs(sin(age + r));
	}
	float SensorAge() {
		return age/generationLength;
	}

	//Akcije
	void ActionMoveN(){
		if (coord.x != 0 && grid[coord.x - 1][coord.y] <= 0) coord.x -= 1;
	}
	void ActionMoveW() {
		if (coord.y != 0 && (grid[coord.x][coord.y - 1] <= 0)) coord.y -= 1;
	}
	void ActionMoveS() {
		if (coord.x != 99 && grid[coord.x + 1][coord.y] <= 0) coord.x += 1;
	}
	void ActionMoveE() {
		if (coord.y != 99 && grid[coord.x][coord.y + 1] <= 0) coord.y += 1;
	}
	void ActionMoveFW() {
		int x = coord.x - lastCoord.x;
		int y = coord.y - lastCoord.y;
		if (((x == -1 && coord.x != 0) || (x == 1 && coord.x != 99)) && (grid[coord.x + x][coord.y] <= 0)) coord.x += x;
		if (((y == -1 && coord.y != 0) || (y == 1 && coord.y != 99)) && (grid[coord.x][coord.y + y] <= 0)) coord.y += y;
	}
	
	//Inicijalizacija
	void Init() {
		InitGenome();
		//PrintGenome();
		int i = 0;
		for (Gene g : genome) {
			if (g.input_type == Sensor && g.output_type == Neuron) {
				activeSensorsB[g.input] = true;
				neuronInputs[g.output].push_back(g.input);
				neuronInputW[g.output].push_back(g.weight);
			}
			if (g.input_type == Neuron && g.output_type == Action) {
				activeActionsB[g.output] = true;
				actionInputs[g.output].push_back(g.input);
				actionInputW[g.output].push_back(g.weight);

			}
			if (g.input_type == Sensor && g.output_type == Action) {
				activeSensorsB[g.input] = true;
				activeActionsB[g.output] = true;
				directConn[g.output].push_back(g.input);
				directConnW[g.output].push_back(g.weight);
			}
		}
		for (int i = 0; i < END_S; ++i) {
			if (activeSensorsB[i]) activeSensors.push_back(i);
		}
		for (int i = 0; i < END_A; ++i) {
			if (activeActionsB[i]) activeActions.push_back(i);
		}
	}

	// Uzimanje vrednosti svakog od aktivnih cula (poziva se u svakom koraku)
	void readSensors() {
		//cout << activeSensors.size() << endl;
		for (int i : activeSensors) {
			switch (i) {
				case X_POS: sensorInput[i] = SensorXPos(coord); break;
				case Y_POS: sensorInput[i] = SensorYPos(coord); break;
				case DIST_FROM_CORNER: sensorInput[i] = SensorDistCorner(coord); break;
				case DIST_FROM_CENTER: sensorInput[i] = SensorDistCenter(coord); break;
				case EDGE_DIST: sensorInput[i] = SensorEDist(coord); break;
				case OSCILATOR: sensorInput[i] = SensorOscilator(); break;
				case FOOD_IN_RAD: sensorInput[i] = SensorFoodRad(coord,9); break;
				case POPULATION_DENSITY: sensorInput[i] = SensorPopDensity(coord,9); break;
				case AGE: sensorInput[i] = SensorAge(); break;
			}
		}
	}

	//Korak
	void makeStep() {
		readSensors();
		for (int i = 0; i < numberOfNeurons; ++i) {
			neuronInputValue[i] = 0;
			for (int k = 0; k < neuronInputs[i].size(); ++k) {
				neuronInputValue[i] += sensorInput[neuronInputs[i][k]] * neuronInputW[i][k];
			}
			neuronOutputValue[i] = tanh(neuronInputValue[i]);
		}
		for (int i = 0; i < END_A; ++i) {
			actionInputValue[i] = 0;
			for (int k = 0; k < directConn[i].size(); ++k) {
				actionInputValue[i] += sensorInput[directConn[i][k]] * directConn[i][k];
			}
			for (int k = 0; k < actionInputs[i].size(); ++k) {
				actionInputValue[i] += neuronOutputValue[actionInputs[i][k]] * actionInputW[i][k];
			}
			actionOutputValue[i] = tanh(actionInputValue[i]);
		}
		srand(time(0));
		for (int i = 0; i < END_A; ++i) {
			if (randomChance(actionOutputValue[i])) {
				switch (i) {
				case MOVE_FW: ActionMoveFW(); break;
				case MOVE_N: ActionMoveN(); break;
				case MOVE_W: ActionMoveW(); break;
				case MOVE_S: ActionMoveS(); break;
				case MOVE_E: ActionMoveE(); break;
				} 
			}
		}
	}
};

#endif