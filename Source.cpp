#include "SDL.h"
#undef main
#include <iostream>
#include "Program.h"
#include "Organism.h"
#include "Global.h"

Program* prog = nullptr;

int main() {
	//vector<Organism> vecOrg;

	Organism o;
	o.genCode = "01AD003304B606E8E3CB014DA9264AC8585B3CB99203882A23084C491F98FCDA0719297C4A52C3E89D965E2BDE29C0660B85464A105ADD30B288AEF284C0903A";
	/*o.PrintGenome();*/

	/*cout << o.genCode << endl;
	cout << randomGenCode() << endl;*/

	const int frameRate = 60;
	const int frameDelay = 1000 / frameRate;

	Uint32 frameStart;
	int frameTime;

	prog = new Program();

	prog->Init("Program", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, false);

	while (prog->Running()) {
		frameStart = SDL_GetTicks();

		prog->HandleEvents();
		prog->Update();
		prog->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	prog->Clean();
}
