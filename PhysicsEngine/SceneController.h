#pragma once
#include "World.h"
#include "SceneConfig.h"
#include "Blizzard.h"

class SceneController
{
public:
	SceneController(raven::WorldConfiguration& worldConfig);

	void CreateScene(const SceneConfig& sceneConfig);
	void UpdateWorld(float deltaTime);

	raven::core::PackedArray<raven::Particle, 5000>& GetWorldParticles(void);
	std::vector<raven::StaticBox>& GetWorldScenery(void);
	std::vector<raven::SpringJoint>& GetSprings(void);
	std::vector<raven::AnchoredSpring>& GetAnchoredSprings(void);
	std::vector<raven::WindForceGenerator>& GetWindForceGenerator(void);

	void AddStaticBox();
	void AddBall(float x, float y);
	void AddBlizzard(float x, float y);

	void RotateBoxRight();
	void RotateBoxLeft();

protected:
	void CreateCloth(uint32_t columns, uint32_t rows, float nodeSize, const glm::vec2& startP, float offset);
	void SpawnBalls(uint32_t ballCount);
	void CreateDefaultScenery();
	void PlaceDefaultFan();

private:
	raven::WorldConfiguration m_config;
	raven::World* m_world;

	// Gimmick
	raven::StaticBox* m_rotatableBox;
	std::vector<Blizzard> m_blizzards;
};
