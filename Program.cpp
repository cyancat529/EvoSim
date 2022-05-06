#include "Program.h"
#include <iostream>

Program::Program() {
	
}
Program::~Program() {

}

void Program::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	x = 50;
	y = 50;
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
		r1.w = 40;
		r1.h = 40;

		isRunning = true;
	}
	else {
		isRunning = false;
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

		default:
			break;
	}
}
void Program::Update() {
	SDL_GetMouseState(&x, &y);

	r1.x = x-20;
	r1.y = y-20;
}

void Program::Render() {
	SDL_SetRenderDrawColor(rend, 15, 15, 20, 255);
	SDL_RenderClear(rend);
	SDL_SetRenderDrawColor(rend, 255, 0, 20, 255);
	
	SDL_RenderDrawRect(rend, &r1);
	SDL_RenderFillRect(rend, &r1);
	SDL_RenderPresent(rend);
}
void Program::Clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(rend);
	SDL_Quit();
	std::cout << "Quit program" << std::endl;
}
