#include "SDL.h"
#undef main
#include <iostream>
#include "Program.h"
#include "Organism.h"
#include "Global.h"

Program* prog = nullptr;

/*enum Speed {
	SPD_05,
	SPD_1,
	SPD_2,
	SPD_MAX
};*/

int main(int argc, char** argv) {
	int frameRate;
	Param p = InitParam("");

	if (argc == 1) frameRate = 60;
	else {
		string s = argv[1];
		if(s == "0.5") frameRate = 30;
		else if (s == "1") frameRate = 60;
		else if (s == "2") frameRate = 120;
		else if (s == "max") frameRate = 1;
		else frameRate = 60;
	}

	if (argc == 3) {
		string fname = argv[2];
		if(fname.substr(fname.size() - 4, 4) == ".cfg") p = InitParam(fname);
	}
	
	const int frameDelay = 1000 / frameRate;

	Uint32 frameStart;
	int frameTime;

	prog = new Program();

	prog->Init("Program", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, false, p);

	while (prog->Running()) {
		frameStart = SDL_GetTicks();

		prog->HandleEvents();
		prog->Update();
		prog->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime && frameRate != 1) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	prog->Clean();
}
