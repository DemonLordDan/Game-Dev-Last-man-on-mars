#include <iostream>
#include "Game.h"
#include "menu.h"



int main()
{
	// Init Menu
	menu Menu;
	while (Menu.running()) {
		
		// Init srand
		std::srand(static_cast<unsigned>(time(NULL)));

		// Init Game engine
		Game game;

		// Game Loop
		if (Menu.getSNumber() == 1) {
			while (game.running())
			{
				// Update
				game.update();

				// Render
				game.render();
			}
		}
	}

	// Game End
	return 0;
}


