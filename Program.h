#ifndef Program_h
#define Program_h

#include <iostream>
#include <time.h>
#include <vector>
#include <chrono>

#include "SDL.h"
#include "Organism.h"
#include "Global.h"

class Program
{
public:
	Program();
	~Program();

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, Param p);
	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool Running() { return isRunning; };

private:
	chrono::time_point<std::chrono::steady_clock> startT, endT;
	int x;
	int y;
	bool generationInProgress;
	bool isRunning;
	bool reset;
	int steps;
	Param p;
	SDL_Window* window;
	SDL_Renderer* rend;
	SDL_Rect background;
	SDL_Rect button, border1, border2, border3, border4;
	std::vector<SDL_Rect> rect;
	std::vector<Organism> org;
};

#endif