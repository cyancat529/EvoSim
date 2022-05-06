#ifndef Program_h
#define Program_h

#include <stdio.h>
#include "SDL.h"

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
	SDL_Window* window;
	SDL_Renderer* rend;
	SDL_Rect r1;
};

#endif