#include "pch.h"
#include "GameClock.h"
#include "GameTime.h"
#include "World.h"
#include "Settings.h"

#include "Particle.h"

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

#include "BasicSpringDemo.h"

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

using namespace Annulus;
using namespace Demos;

int  main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Annulus Physics Engine Testbed");

	// Create a clock and game time objecs
	GameClock gameClock;
	GameTime gameTime;
	// Create a world with default settings
	Settings settings;
	World world(settings);

	// Create the demo
	BasicSpringDemo springDemo(window, world);
	springDemo.Initialize();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Handle closing of the window
			if (event.type == sf::Event::Closed)
			{ 
				window.close();
			}
			// Handle resizing of screen to not affect the scaling and treat the world to be bigger than the viewport
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, static_cast<std::float_t>(event.size.width), static_cast<std::float_t>(event.size.height));
				window.setView(sf::View(visibleArea));
			}
		}
		// Update game time
		gameClock.UpdateGameTime(gameTime);
		std::chrono::nanoseconds deltaNanoseconds = gameTime.ElapsedGameTime();
		
		// Perform physics update, rendering, etc.
		world.Update(deltaNanoseconds);
		std::cout << "Total Time: " << (gameTime.TotalGameTime().count() / 1000000000.0f) << std::endl;
		
		// Update the demo scene
		springDemo.Update(deltaNanoseconds);

		// Rendering
		window.clear(sf::Color(100, 149, 237, 1));
		
		springDemo.Draw();
		
		window.display();
	}
	return 0;
}