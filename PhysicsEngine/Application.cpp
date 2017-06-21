#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Clock.h"
#include "PackedArray.h"
#include "Particle.h"
#include "WorldRenderer.h"
#include "World.h"
#include "WorldConfiguration.h"
#include <iostream>

int main()
{
	sf::VideoMode mode(1028, 720);
	sf::RenderWindow window(mode, "Physics Engine @ Lukas Vogl");

	/*
	 * Setup variables needed for the Semi-Fixed timestep loop wiht interpolation
	 */
	float t = 0.0f;
	float dt = 0.016f;

	raven::Clock clock;
	clock.Start();

	float currentTime = clock.GetElapsedTime().count();
	float accumulator = 0.0f;

	raven::WorldRenderer rednerer(window);

	raven::WorldConfiguration worldConfig;
	worldConfig.maxParticles = 100000;
	worldConfig.gravitation = { 0.0f, 9.81f };

	raven::World world(worldConfig);
	raven::core::ResourceID one = world.AddParticle({ 100, 100 }, BODY);
	raven::core::ResourceID two = world.AddParticle({ 100, 200 }, BODY);
	
	world.AddAnchoredSpring(one, glm::vec2(100, 80), 1.0f, 5.0f);
	world.AddSpringJoint(one, two, 0.5f, 100.0f);

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

		if (frameTime > 0.25f)
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
			world.Step(dt);
			t += dt;
			accumulator -= dt;
		}
		 /*
		 * Render part of the game loop
		 */
		window.clear(sf::Color::White);

		const raven::core::PackedArray<raven::Particle, 1000>& parti = world.GetParticles();

		for (size_t i = 0; i < parti.Size(); i++)
		{
			raven::Particle p = parti[i];
			rednerer.DrawSphere(p.position, sf::Color::Red, 10.0f);
		}

		window.display();
	}

	return 0;
}
