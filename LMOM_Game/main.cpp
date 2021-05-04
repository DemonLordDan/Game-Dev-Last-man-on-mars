/*
Title: Main
Description: This is where the system starts and finishes, when the game loop stops running, the system returns to here.
Author: Andrew Morrison
*/
#include <iostream>
#include "Game.h"
#include "MainMenu.h"
#include "Leaderboard.h"
#include <time.h>

int main()
{
	// Init random number seed
	srand(time(static_cast<unsigned>(0)));

	bool running = true;
	int choice;

	while (running)
	{
		MainMenu mainMenu;
		choice = mainMenu.run();

		if (choice == 1)
		{
			mainMenu.close();
			Game game;
			game.run();
		}
		else if (choice == 2)
		{
			mainMenu.close();
			Leaderboard leaderboard;
			leaderboard.run();
		}
		else if (choice == 3)
		{
			running = false;
		}
	}


	// Game End
	return 0;
}


