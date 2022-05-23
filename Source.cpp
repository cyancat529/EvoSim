#include "SDL.h"
#undef main
#include <iostream>
#include "Program.h"
#include "Organism.h"
#include "Global.h"

Program* prog = nullptr;

int main() {
	/*const int frameRate = 60;
	const int frameDelay = 1000 / frameRate;*/

	Uint32 frameStart;
	int frameTime;

	prog = new Program();

	prog->Init("Program", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 400, false);

	while (prog->Running()) {
		frameStart = SDL_GetTicks();

		prog->HandleEvents();
		prog->Update();
		prog->Render();

		/*frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}*/
	}

	prog->Clean();
}
