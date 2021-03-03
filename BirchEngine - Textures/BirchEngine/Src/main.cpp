#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{

	const int fps = 60; //target fps
	const int frameDelay = 1000 / fps; //max time between frames

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("GameWindow", 800, 640, false); //divisible by 32

	while (game->running())
	{

		frameStart = SDL_GetTicks();


		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return 0;
}