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
		void DrawBox(const glm::vec2& center, const glm::vec2& extend, const sf::Color& color, float rotation);

	private:
		sf::RenderWindow& m_renderWindow;
	};
}

