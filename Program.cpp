#include "Program.h"
#include "Global.h"
#include "Randomize.h"
#include "InitGen.h"
#include <iostream>
#include <iomanip>

using namespace std;

int grid[100][100];
int generationNumber;

Program::Program() {
	
}
Program::~Program() {

}

void Program::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, Param par) {
	int flags = 0;
	generationNumber = 1;
	generationInProgress = true;
	steps = 0;
	startT = std::chrono::high_resolution_clock::now();
	p = par;

	if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialized..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) std::cout << "Window Created" << std::endl;

		rend = SDL_CreateRenderer(window, -1, flags);
		if (rend) {
			SDL_SetRenderDrawColor(rend, 15, 15, 20, 255);
			std::cout << "Renderer Created" << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	memset(grid, 0, sizeof(grid));

	srand(time(0));

	for (int i = 0; i < p.generationSize; ++i) {
		Organism temp;
		temp.genCode = randomGenCode(p);
		temp.Init(p);

		if (i == 0) {
			x = rand() % 100;
			y = rand() % 100;
			temp.coord.x = x;
			temp.coord.y = y;
			temp.lastCoord.x = x;
			temp.lastCoord.y = y;
			temp.id = i + 1;
			org.push_back(temp);
			grid[x][y] = i+1;
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
			org.push_back(temp);
			grid[x][y] = i + 1;
		}
	}

	int survivalRange = p.survivalRange;

	background.x = 0;
	background.y = 0;
	background.w = 400;
	background.h = 400;

	button.x = 550;
	button.y = 300;
	button.w = 100;
	button.h = 50;

	if (p.survivalCrit == 0) {
		border1.x = 0;
		border1.y = 0;
		border1.w = 4 * survivalRange;
		border1.h = 400;

		border2.x = 400 - 4 * survivalRange;
		border2.y = 0;
		border2.w = 4 * survivalRange;
		border2.h = 400;
	}
	if (p.survivalCrit == 1) {
		border1.x = 0;
		border1.y = 0;
		border1.h = 4 * survivalRange;
		border1.w = 400;

		border2.x = 0;
		border2.y = 400 - 4 * survivalRange;
		border2.h = 4 * survivalRange;
		border2.w = 400;
	}

	if (p.survivalCrit == 2) {
		border1.x = 0;
		border1.y = 0;
		border1.w = 4 * survivalRange;
		border1.h = 4 * survivalRange;

		border2.x = 400 - 4 * survivalRange;
		border2.y = 0;
		border2.w = 4 * survivalRange;
		border2.h = 4 * survivalRange;

		border3.x = 0;
		border3.y = 400 - 4 * survivalRange;
		border3.h = 4 * survivalRange;
		border3.w = 4 * survivalRange;

		border4.x = 400 - 4 * survivalRange;
		border4.y = 400 - 4 * survivalRange;
		border4.h = 4 * survivalRange;
		border4.w = 4 * survivalRange;
	}
}

void Program::HandleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_g && !generationInProgress && !p.autorun) {
				generationInProgress = true;
				generationNumber++;
				steps = 0;
				org = InitGen(org, generationNumber, p.generationSize, p);
			}
			break;

		default:
			break;
	}
}

void Program::Update() {
	rect.clear();

	if (p.autorun && generationNumber <= p.autorunNumOfGen && !generationInProgress) {
		generationInProgress = true;
		generationNumber++;
		steps = 0;
		org = InitGen(org, generationNumber, p.generationSize, p);
		if (generationNumber == p.autorunNumOfGen) {
			p.autorun = false;
		}
	}

	if(steps < 300 && generationInProgress) {
		for (int i = 0; i < org.size(); ++i) {
			Coord cTemp;
			cTemp.x = org[i].coord.x;
			cTemp.y = org[i].coord.y;
			org[i].age += 1;
			org[i].lastCoord = cTemp;
			org[i].makeStep();
			grid[cTemp.x][cTemp.y] = 0;
			grid[org[i].coord.x][org[i].coord.y] = org[i].id;
		}
	}
	if (steps == 300) {
		generationInProgress = false;
		endT = std::chrono::high_resolution_clock::now();
		float exTime = float(std::chrono::duration_cast<std::chrono::milliseconds>(endT - startT).count()) / 1000;
		cout << "Execution time: " << exTime << "s" << endl;
	}


	for (Organism i : org) {
		SDL_Rect r;
		r.x = i.coord.x * 4;
		r.y = i.coord.y * 4;
		r.w = 4;
		r.h = 4;
		rect.push_back(r);
	}

	steps += 1;
}

void Program::Render() {
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
	SDL_RenderClear(rend);

	SDL_SetRenderDrawColor(rend, 15, 15, 20, 255);
	SDL_RenderDrawRect(rend, &background);
	SDL_RenderFillRect(rend, &background);

	SDL_SetRenderDrawColor(rend, 40, 80, 125, 255);
	SDL_RenderDrawRect(rend, &border1);
	SDL_RenderFillRect(rend, &border1);

	SDL_RenderDrawRect(rend, &border2);
	SDL_RenderFillRect(rend, &border2);

	SDL_RenderDrawRect(rend, &border3);
	SDL_RenderFillRect(rend, &border3);

	SDL_RenderDrawRect(rend, &border4);
	SDL_RenderFillRect(rend, &border4);
	
	/*SDL_SetRenderDrawColor(rend, 255, 15, 45, 255);
	SDL_RenderDrawRect(rend, &button);
	SDL_RenderFillRect(rend, &button);*/

	//if(generationInProgress) SDL_SetRenderDrawColor(rend, 255, 0, 20, 255);
	//else SDL_SetRenderDrawColor(rend, 0, 255, 20, 255);
	//else //SDL_SetRenderDrawColor(rend, 20, 0, 255, 255);

	for (SDL_Rect i : rect) {
		Coord temp;
		temp.x = i.x / 4;
		temp.y = i.y / 4;
		if (p.survivalCrit == 0 && survivalCriteriaWE(temp, p.survivalRange)) SDL_SetRenderDrawColor(rend, 0, 255, 20, 255);
		else if (p.survivalCrit == 1 && survivalCriteriaNS(temp, p.survivalRange)) SDL_SetRenderDrawColor(rend, 0, 255, 20, 255);
		else if (p.survivalCrit == 2 && survivalCriteriaCORN(temp, p.survivalRange)) SDL_SetRenderDrawColor(rend, 0, 255, 20, 255);
		else SDL_SetRenderDrawColor(rend, 255, 0, 20, 255);

		SDL_RenderDrawRect(rend, &i);
		SDL_RenderFillRect(rend, &i);
	}
	
	SDL_RenderPresent(rend);

	reset = false;
}
void Program::Clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(rend);
	SDL_Quit();
	std::cout << "Quit program" << std::endl;
}
