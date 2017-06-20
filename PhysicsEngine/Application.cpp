#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Clock.h"

int main()
{
	sf::VideoMode mode(1028, 720);
	sf::RenderWindow window(mode, "Physics Engine @ Lukas Vogl");

	/*
	 * Setup variables needed for the Semi-Fixed timestep loop wiht interpolation
	 */
	float t = 0.0f;
	float dt = 0.0016f;

	raven::Clock clock;
	clock.Start();

	float currentTime = clock.GetElapsedTime().count();
	float accumulator = 0.0f;

	while (window.isOpen())
	{
		/**
		* Input part of the game loop
		*/
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		float newTime = clock.GetElapsedTime().count();
		float frameTime = newTime - currentTime;
		if (frameTime < 0.25f)
		{
			frameTime = 0.25f;
		}
		currentTime = newTime;

		accumulator += frameTime;

		/**
		 * Update part of the game loop
		 */
		while (accumulator >= dt)
		{
			// Update physic world
			t += dt;
			accumulator -= dt;
		}

		// Here we should apply the interpolations tep of the game loop
		//const double alpha = accumulator / dt;

		//State state = currentState * alpha +
			//previousState * (1.0 - alpha);

		 /*
		 * Render part of the game loop
		 */
		window.clear(sf::Color::White);

		window.display();
	}

	return 0;
}
