#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Clock.h"
#include "PackedArray.h"
#include "Particle.h"
#include "WorldRenderer.h"
#include "World.h"
#include "WorldConfiguration.h"
#include "StaticBox.h"
#include "Blizzard.h"
#include <iostream>
#include "SceneController.h"

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
	worldConfig.gravitation = { 0.0f, 100.9f };
	worldConfig.collisionIterations = 5;

	//raven::World world(worldConfig);
	//raven::core::ResourceID one = world.AddParticle({ 100, 100 }, BODY);
	//raven::core::ResourceID two = world.AddParticle({ 100, 150 }, BODY);
	//raven::core::ResourceID three = world.AddParticle({ 150, 100 }, BODY);
	//raven::core::ResourceID four = world.AddParticle({ 150, 150 }, BODY);
	//raven::core::ResourceID five = world.AddParticle({ 200, 100 }, BODY);
	//raven::core::ResourceID six = world.AddParticle({ 200, 150 }, BODY);
	//raven::core::ResourceID seven = world.AddParticle({ 100, 200 }, BODY);
	//raven::core::ResourceID eight = world.AddParticle({ 150, 200 }, BODY);
	//raven::core::ResourceID nine = world.AddParticle({ 200, 200 }, BODY);

	//raven::core::ResourceID ten = world.AddParticle({ 300, 300 }, BODY);
	//world.GetParticles().Lookup(ten)->inverseMass = 4.0f;

	//raven::core::ResourceID eleven = world.AddParticle({ 320, 300 }, BODY);
	//world.GetParticles().Lookup(eleven)->inverseMass = 4.0f;

	//raven::core::ResourceID twelve = world.AddParticle({ 340, 300 }, BODY);
	//world.GetParticles().Lookup(twelve)->inverseMass = 4.0f;

	//raven::core::ResourceID thriteen = world.AddParticle({ 600, 325 }, BODY);
	//world.GetParticles().Lookup(thriteen)->inverseMass = 4.0f;
	//world.GetParticles().Lookup(thriteen)->velocity = {600.0f, 0};
	//
	//world.AddAnchoredSpring(one, glm::vec2(100, 50), 10.0f, 2.0f);
	//world.AddAnchoredSpring(three, glm::vec2(150, 50), 10.0f, 2.0f);
	//world.AddAnchoredSpring(five, glm::vec2(200, 50), 10.0f, 2.0f);

	//float springConstant = 10.0f;
	//float restLength = 35.0f;

	//world.AddSpringJoint(one, two, springConstant, restLength);
	//world.AddSpringJoint(two, seven, springConstant, restLength);
	//world.AddSpringJoint(three, four, springConstant, restLength);
	//world.AddSpringJoint(four, eight, springConstant, restLength);
	//world.AddSpringJoint(five, six, springConstant, restLength);
	//world.AddSpringJoint(six, nine, springConstant, restLength);

	//world.AddSpringJoint(one, three, springConstant, restLength);
	//world.AddSpringJoint(three, five, springConstant, restLength);

	//world.AddSpringJoint(two, four, 1.0f, restLength);
	//world.AddSpringJoint(four, six, 1.0f, restLength);

	//world.AddSpringJoint(seven, eight, 1.0f, restLength);
	//world.AddSpringJoint(eight, nine, 1.0f, restLength);

	//world.AddStaticBox({ 200, 400 }, { 600, 25 }, 40);
	//world.AddStaticBox({ 600, 710 }, { 1600, 25 }, 0);

	//eleven = world.AddParticle({ 800, 500 }, BODY);
	//world.GetParticles().Lookup(eleven)->inverseMass = 4.0f;
	//eleven = world.AddParticle({ 780, 500 }, BODY);
	//world.GetParticles().Lookup(eleven)->inverseMass = 4.0f;
	//eleven = world.AddParticle({ 820, 500 }, BODY);
	//world.GetParticles().Lookup(eleven)->inverseMass = 4.0f;
	//eleven = world.AddParticle({ 790, 600 }, BODY);
	//world.GetParticles().Lookup(eleven)->inverseMass = 4.0f;
	//eleven = world.AddParticle({ 820, 500 }, BODY);
	//world.GetParticles().Lookup(eleven)->inverseMass = 4.0f;

	//eleven = world.AddParticle({ 0, 50 }, BODY);
	//world.GetParticles().Lookup(eleven)->inverseMass = 4.0f;
	//world.GetParticles().Lookup(eleven)->velocity = { 200.0f, 0 };

	//world.AddStaticBox({ 800, 410 }, { 200, 25 }, 0);
	//world.AddStaticBox({ 675, 710 }, { 25, 300 }, 0);
	//world.AddStaticBox({ 925, 710 }, { 25, 300 }, 0);

	//raven::WindForceGenerator& f = world.AddWindForceGenerator({ 800, 300 }, { -1, 0 }, 100.0f);
	//f.SetBounds({ 100, 300 });
	//f.SetDistance(500);

	//Blizzard bliz({500, 200}, 300.0f, 0.1f, world);
	//Blizzard bliz2({800, 100}, 300.0f, 0.1f, world);

	SceneController scene(worldConfig);

	SceneConfig config;
	scene.CreateScene(config);

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

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Key::Right)
				{
					scene.RotateBoxRight();
				}

				if (event.key.code == sf::Keyboard::Key::Left)
				{
					scene.RotateBoxLeft();
				}

				if (event.key.code == sf::Keyboard::Key::R)
				{
					scene.CreateScene(config);
				}

				if (event.key.code == sf::Keyboard::Key::Space)
				{
					scene.GetWindForceGenerator().back().ToggleState();
				}
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				float x = event.mouseButton.x;
				float y = event.mouseButton.y;
				scene.AddBall(x, y);
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
			scene.UpdateWorld(dt);
			t += dt;
			accumulator -= dt;
		}
		 /*
		 * Render part of the game loop
		 */
		window.clear(sf::Color::Black);

		raven::core::PackedArray<raven::Particle, 5000>& parti = scene.GetWorldParticles();

		//std::cout << parti.Size() << std::endl;

		std::vector<raven::StaticBox>& scenery = scene.GetWorldScenery();
		for (size_t i = 0; i < scenery.size(); i++)
		{
			raven::StaticBox& box = scenery[i];

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
		}

		std::vector<raven::SpringJoint>& springs = scene.GetSprings();
		for (size_t i = 0; i < springs.size(); i++)
		{
			raven::SpringJoint& spring = springs[i];
			raven::Particle* p1 = parti.Lookup(spring.GetParticle(0));
			raven::Particle* p2 = parti.Lookup(spring.GetParticle(1));

			rednerer.DrawLine(p1->position, p2->position, sf::Color::Red);
		}

		std::vector<raven::AnchoredSpring>& anchoredSprings = scene.GetAnchoredSprings();
		for (size_t i = 0; i < anchoredSprings.size(); i++)
		{
			raven::AnchoredSpring& spring = anchoredSprings[i];
			raven::Particle* p1 = parti.Lookup(spring.GetParticle());

			rednerer.DrawSphere(spring.GetAnchor(), sf::Color::Magenta, 5.0f);
			rednerer.DrawLine(p1->position, spring.GetAnchor(), sf::Color::Blue);
		}

		std::vector<raven::WindForceGenerator>& windForces = scene.GetWindForceGenerator();
		for (size_t i = 0; i < windForces.size(); i++)
		{
			raven::WindForceGenerator& windForce = windForces[i];

			glm::vec2 p1 = { windForce.GetPosition().x - 10.0f, windForce.m_lower_upperBounds.x };
			glm::vec2 p2 = { windForce.GetPosition().x + 10.0f, windForce.m_lower_upperBounds.x };
			glm::vec2 p3 = { windForce.GetPosition().x + 10.0f, windForce.m_lower_upperBounds.y };
			glm::vec2 p4 = { windForce.GetPosition().x - 10.0f, windForce.m_lower_upperBounds.y };

			rednerer.DrawBox(p1, p2, p3, p4, sf::Color::Yellow, true);

		}

		for (size_t i = 0; i < parti.Size(); i++)
		{
			raven::Particle p = parti[i];
			
			if (p.type == BODY)
			{
				if (p.material == raven::STEEL)
				{
					rednerer.DrawSphere(p.position, sf::Color::Cyan, p.radius);
				}
				else if (p.material == raven::STEEL_LUBRICATED)
				{
					rednerer.DrawSphere(p.position, sf::Color::Magenta, p.radius);
				}
			}
			else
			{
				rednerer.DrawPoint(p.position, sf::Color::White);
			}
		}

		window.display();
	}

	return 0;
}
