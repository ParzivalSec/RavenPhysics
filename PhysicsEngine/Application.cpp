#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Clock.h"
#include "PackedArray.h"
#include "Particle.h"
#include "WorldRenderer.h"
#include "World.h"
#include "WorldConfiguration.h"
#include "StaticBox.h"

int main()
{
	sf::VideoMode mode(1280, 720);
	sf::ContextSettings context(0, 0, 8);
	sf::RenderWindow window(mode, "Physics Engine @ Lukas Vogl", sf::Style::Default, context);

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
	raven::core::ResourceID two = world.AddParticle({ 100, 150 }, BODY);
	raven::core::ResourceID three = world.AddParticle({ 150, 100 }, BODY);
	raven::core::ResourceID four = world.AddParticle({ 150, 150 }, BODY);
	raven::core::ResourceID five = world.AddParticle({ 200, 100 }, BODY);
	raven::core::ResourceID six = world.AddParticle({ 200, 150 }, BODY);
	raven::core::ResourceID seven = world.AddParticle({ 100, 200 }, BODY);
	raven::core::ResourceID eight = world.AddParticle({ 150, 200 }, BODY);
	raven::core::ResourceID nine = world.AddParticle({ 200, 200 }, BODY);
	
	world.AddAnchoredSpring(one, glm::vec2(100, 50), 1.0f, 5.0f);
	world.AddAnchoredSpring(three, glm::vec2(150, 50), 1.0f, 5.0f);
	world.AddAnchoredSpring(five, glm::vec2(200, 50), 1.0f, 5.0f);

	float restLength = 35.0f;

	world.AddSpringJoint(one, two, 1.0f, restLength);
	world.AddSpringJoint(two, seven, 1.0f, restLength);
	world.AddSpringJoint(three, four, 1.0f, restLength);
	world.AddSpringJoint(four, eight, 1.0f, restLength);
	world.AddSpringJoint(five, six, 1.0f, restLength);
	world.AddSpringJoint(six, nine, 1.0f, restLength);

	world.AddSpringJoint(one, three, 1.0f, restLength);
	world.AddSpringJoint(three, five, 1.0f, restLength);

	world.AddSpringJoint(two, four, 1.0f, restLength);
	world.AddSpringJoint(four, six, 1.0f, restLength);

	world.AddSpringJoint(seven, eight, 1.0f, restLength);
	world.AddSpringJoint(eight, nine, 1.0f, restLength);

	world.AddWindForceGenerator({ 0, 200 }, { 1, 0 }, 10.0f);

	raven::StaticBox box({ 350, 600 }, 800, 50);
	box.Rotate(20);

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

		raven::core::PackedArray<raven::Particle, 1000>& parti = world.GetParticles();

		raven::core::OOBB oriented_bb = box.GetOOBB();
		// OOBB
		glm::vec2 p1 = oriented_bb.center - box.GetOOBB().axis[1] * oriented_bb.w_h_halfExtend.y
			- oriented_bb.axis[0] * oriented_bb.w_h_halfExtend.x;
		glm::vec2 p2 = oriented_bb.center - oriented_bb.axis[1] * oriented_bb.w_h_halfExtend.y
			+ oriented_bb.axis[0] * oriented_bb.w_h_halfExtend.x;
		glm::vec2 p3 = oriented_bb.center + oriented_bb.axis[1] * oriented_bb.w_h_halfExtend.y
			+ oriented_bb.axis[0] * oriented_bb.w_h_halfExtend.x;
		glm::vec2 p4 = oriented_bb.center + oriented_bb.axis[1] * oriented_bb.w_h_halfExtend.y
			- oriented_bb.axis[0] * oriented_bb.w_h_halfExtend.x;

		rednerer.DrawBox(p1, p2, p3, p4, sf::Color::Green, false);

		std::vector<raven::SpringJoint> springs = world.GetSpringJoints();
		for (size_t i = 0; i < springs.size(); i++)
		{
			raven::SpringJoint& spring = springs[i];
			raven::Particle* p1 = parti.Lookup(spring.GetParticle(0));
			raven::Particle* p2 = parti.Lookup(spring.GetParticle(1));

			rednerer.DrawLine(p1->position, p2->position, sf::Color::Red);
		}

		std::vector<raven::AnchoredSpring> anchoredSprings = world.GetAnchoredSprings();
		for (size_t i = 0; i < anchoredSprings.size(); i++)
		{
			raven::AnchoredSpring& spring = anchoredSprings[i];
			raven::Particle* p1 = parti.Lookup(spring.GetParticle());

			rednerer.DrawSphere(spring.GetAnchor(), sf::Color::Magenta, 5.0f);
			rednerer.DrawLine(p1->position, spring.GetAnchor(), sf::Color::Blue);
		}

		for (size_t i = 0; i < parti.Size(); i++)
		{
			raven::Particle p = parti[i];
			rednerer.DrawSphere(p.position, sf::Color::Red, 10.0f);
		}

		window.display();
	}

	return 0;
}
