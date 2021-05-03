#pragma once
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
		
		Menu.update();
		
		Menu.render();

		// Game Loop
		if (Menu.getSNumber() == 1) {
			// Init Game engine
			Game game;
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


