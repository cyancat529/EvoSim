#ifndef Program_h
#define Program_h

#include <iostream>
#include <time.h>
#include <vector>

#include "SDL.h"
#include "Organism.h"
#include "Global.h"

class Program
{
public:
	Program();
	~Program();

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool Running() { return isRunning; };

private:
	int x;
	int y;
	bool isRunning;
	bool reset;
	SDL_Window* window;
	SDL_Renderer* rend;
	std::vector<SDL_Rect> rect;
	std::vector<Organism> org;
	Organism temp;
	Organism* grid[40][40] = {};
};

#endif