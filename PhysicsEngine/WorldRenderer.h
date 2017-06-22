#pragma once

#include "vec2.hpp"
#include <SFML/Graphics/Color.hpp>

namespace sf
{
	class RenderWindow;
}

namespace raven
{
	class World;

	class WorldRenderer
	{
	public:
		WorldRenderer(sf::RenderWindow& renderWindow);

		void DrawSphere(const glm::vec2& center, const sf::Color& color, float radius);
		void DrawBox(const glm::vec2& center, const glm::vec2& extend, const sf::Color& color, float rotation, bool wireFrame);
		void DrawBox(const glm::vec2& pointA, const glm::vec2& pointB, const glm::vec2& pointC, const glm::vec2& pointD, const sf::Color& color, bool wireFrame);

		void DrawLine(const glm::vec2& pointA, const glm::vec2& pointB, const sf::Color& color);
		void DrawPoint(const glm::vec2& point, const sf::Color& color);

	private:
		sf::RenderWindow& m_renderWindow;
	};
}

