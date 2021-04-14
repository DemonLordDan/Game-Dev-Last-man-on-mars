#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


using namespace std;
//using namespace sf;

int main()
{
	// Initialize Window
	sf::RenderWindow window(sf::VideoMode(640, 480), "Last Man on Mars", sf::Style::Titlebar | sf::Style::Close);
	sf::Event ev;

	// Game Loop
	while (window.isOpen())
	{
		// Event Polling
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				break;
			}
		}

		// Update

		// Render
		window.clear(sf::Color::Cyan); // Clear old Frame

		// Draw the game

		window.display(); // Tell game that the window has finished drawing
	}

	// Game End
	return 0;
}

