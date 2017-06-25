#include "SceneController.h"
#include "Blizzard.h"

SceneController::SceneController(raven::WorldConfiguration& worldConfig) 
	: m_config(worldConfig)
	, m_world(nullptr)
{}

void SceneController::CreateScene(const SceneConfig& sceneConfig)
{
	if (m_world != nullptr)
	{
		delete m_world;
		m_blizzards.clear();
	}

	m_world = new raven::World(m_config);

	CreateDefaultScenery();
	PlaceDefaultFan();

	CreateCloth(10, 6, 5.5f, { 400, 50 }, 40);
	AddBlizzard(100, 50);
	AddBlizzard(1000, 25);
}

void SceneController::UpdateWorld(float deltaTime)
{
	for (Blizzard& blizz : m_blizzards)
	{
		blizz.Update(deltaTime);
	}

	m_world->Step(deltaTime);
}

raven::core::PackedArray<raven::Particle, 5000>& SceneController::GetWorldParticles()
{
	return m_world->GetParticles();
}

std::vector<raven::StaticBox>& SceneController::GetWorldScenery()
{
	return m_world->GetScenery();
}

std::vector<raven::SpringJoint>& SceneController::GetSprings()
{
	return m_world->GetSpringJoints();
}

std::vector<raven::AnchoredSpring>& SceneController::GetAnchoredSprings()
{
	return m_world->GetAnchoredSprings();
}

std::vector<raven::WindForceGenerator>& SceneController::GetWindForceGenerator()
{
	return m_world->GetWindForceGenerator();
}

void SceneController::AddStaticBox() {}

void SceneController::AddBall(float x, float y)
{
	raven::core::ResourceID id = m_world->AddParticle({ x, y }, BODY);
	raven::Particle& particle = *m_world->GetParticles().Lookup(id);
	particle.velocity = { 100, 0 };
	particle.material = raven::STEEL_LUBRICATED;
	particle.restitution = 1.0f;
}

void SceneController::AddBlizzard(float x, float y)
{
	Blizzard blizz({x, y}, 100.0f, 0.05f, *m_world);
	m_blizzards.push_back(blizz);
}

void SceneController::RotateBoxRight()
{
	m_rotatableBox->Rotate(5.0f);
}

void SceneController::RotateBoxLeft()
{
	m_rotatableBox->Rotate(-5.0f);
}

void SceneController::CreateCloth(uint32_t columns, uint32_t rows, float nodeSize, const glm::vec2& startP, float offset)
{
	glm::vec2 p = startP;
	std::vector<raven::core::ResourceID> previousRow;
	previousRow.resize(columns);
	// Create row by row, first row beeing anchor springs
	for (size_t row = 0; row < rows; row++)
	{
		for (size_t col = 0; col < columns; col++)
		{
			raven::core::ResourceID clothNode = m_world->AddParticle(p, BODY);
			raven::Particle* clothPart = m_world->GetParticles().Lookup(clothNode);
			clothPart->radius = nodeSize;
			clothPart->inverseMass = 0.8f;

			if (row == 0)
			{
				// We want to create anchor springs
				m_world->AddAnchoredSpring(clothNode, { p.x, p.y - offset }, 10.0f, offset);
				previousRow[col] = clothNode;


				if (col != 0)
				{
					m_world->AddSpringJoint(previousRow[col - 1], clothNode, 0.2f, offset);
				}
			}
			else
			{
				m_world->AddSpringJoint(clothNode, previousRow[col], 30.5f, offset);

				if (col != 0)
				{
					m_world->AddSpringJoint(previousRow[col - 1], clothNode, 0.2f, offset);
				}

				previousRow[col] = clothNode;
			}

			p.x += offset;
		}
		p.y += offset;
		p.x = startP.x;
	}
}

void SceneController::SpawnBalls(uint32_t ballCount) {}

void SceneController::CreateDefaultScenery()
{
	// Ground plane
	m_world->AddStaticBox({ 640, 710 }, { 1280, 25 }, 0);

	// Right terasse
	m_world->AddStaticBox({ 800, 500 }, { 500, 25 }, 0);

	// Roof Boxes
	m_world->AddStaticBox({ 880, 300 }, { 200, 25 }, -35);
	m_world->AddStaticBox({ 1150, 600 }, { 200, 25 }, -35);

	// Left slider
	m_rotatableBox = &m_world->AddStaticBox({ 50, 400 }, { 600, 25 }, 25);
	m_rotatableBox->material = raven::STEEL_LUBRICATED;
}

void SceneController::PlaceDefaultFan()
{
	raven::WindForceGenerator& defaultFan = m_world->AddWindForceGenerator({ 1100, 450 }, { -1, 0 }, 100.0f);
	defaultFan.SetBounds({ 100, 500 });
	defaultFan.SetDistance(1000);
}
