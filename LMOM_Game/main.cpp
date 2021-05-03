#include <iostream>
#include "Game.h"
#include <time.h>

int main()
{
	// Init random number seed
	srand(time(static_cast<unsigned>(0)));

	Game game;

	game.run();


	// Game End
	return 0;
}


