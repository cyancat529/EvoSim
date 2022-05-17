#include "Program.h"
#include "Global.h"
#include <iostream>

using namespace std;

Program::Program() {
	
}
Program::~Program() {

}

void Program::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
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


	for (int i = 0; i < 20; ++i) {
		srand(time(0));

		if (i == 0) {
			x = rand() % 100;
			y = rand() % 100;
			temp.coord.x = x;
			temp.coord.y = y;
			org.push_back(temp);
			grid[x][y] = &org.back();
		}
		else {
			cout << "pocetak" << endl;
			bool pass = false;
			while (!pass) {
				x = rand() % 100;
				y = rand() % 100;
				if (grid[x][y] == NULL) pass = true;
			}
			cout << "kraj" << endl;
			temp.coord.x = x;
			temp.coord.y = y;
			org.push_back(temp);
			grid[x][y] = &org.back();
		}
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
			if (event.key.keysym.sym == SDLK_t) reset = true;
			else reset = false;
			break;

		default:
			break;
	}
}

void Program::Update() {
	rect.clear();

	for (Organism i : org) {
		SDL_Rect r;
		r.x = i.coord.x * 4;
		r.y = i.coord.y * 4;
		r.w = 4;
		r.h = 4;
		rect.push_back(r);
	}

	if (reset) {
		cout << "Reset" << endl;
	}
}

void Program::Render() {
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	SDL_SetRenderDrawColor(rend, 15, 15, 20, 255);
	SDL_RenderClear(rend);
	if (keystates[SDL_SCANCODE_R]) SDL_SetRenderDrawColor(rend, 0, 255, 20, 255);
	else if(!reset) SDL_SetRenderDrawColor(rend, 255, 0, 20, 255);
	else SDL_SetRenderDrawColor(rend, 20, 0, 255, 255);
	
	for (SDL_Rect i : rect) {
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
