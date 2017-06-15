#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Clock.h"
#include "Particle.h"
#include "ParticleForceRegistry.h"
#include "FanForceGenerator.h"
#include "ParticleSpring.h"
#include "GravitationForceGenerator.h"

int main()
{
	sf::VideoMode mode(1028, 720);
	sf::RenderWindow window(mode, "Physics Engine @ Lukas Vogl");

	raven::ParticleForceRegistry registry;
	std::vector<raven::Particle*> particles;

	raven::GravitationForceGenerator gravitation(glm::vec2(0.0f, 10.0f));
	raven::FanForceGenerator fan(glm::vec2(1.0f, 0.0f), 0.0f);

	// Create first particle
	raven::Particle* part1 = new raven::Particle(glm::vec2(10.0f, 10.0f), glm::vec2(0.0f, 0.0f));
	part1->SetMass(1.0f);
	particles.push_back(part1);

	raven::Particle* part2 = new raven::Particle(glm::vec2(30.0f, 11.0f), glm::vec2(0.0f, 0.0f));
	part2->SetMass(1.0f);

	raven::Particle* part3 = new raven::Particle(glm::vec2(10.0f, 22.0f), glm::vec2(0.0f, 0.0f));
	part3->SetMass(1.0f);

	raven::ParticleSpring spring(part1, 0.1f, 10.0f);
	registry.Register(part2, &spring);

	raven::ParticleSpring sprin2(part2, 0.1f, 10.0f);
	registry.Register(part3, &spring);

	raven::ParticleSpring sprin3(part3, 0.1f, 10.0f);
	registry.Register(part2, &spring);

	registry.Register(part2, &gravitation);
	registry.Register(part3, &gravitation);

	registry.Register(part2, &fan);
	registry.Register(part3, &fan);

	particles.push_back(part2);
	particles.push_back(part3);
	/*
	 * Setup variables needed for the Semi-Fixed timestep loop wiht interpolation
	 */
	float t = 0.0f;
	float dt = 0.01f;

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

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::L)
			{
				static float val = 1.0f;
				fan.SetStrength(val++);
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
			registry.UpdateForces(dt);
			// Update physic world
			for (size_t i = 0; i < particles.size(); i++)
			{
				particles[i]->Integrate(dt);
			}

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

		sf::CircleShape part;
		part.setFillColor(sf::Color::Blue);
		part.setRadius(10.0f);
		part.setOrigin(10.0f, 10.0f);

		for (size_t i = 0; i < particles.size(); i++)
		{
			part.setPosition(particles[i]->GetPosition().x, particles[i]->GetPosition().y);
			window.draw(part);
		}

		window.display();
	}

	return 0;
}
