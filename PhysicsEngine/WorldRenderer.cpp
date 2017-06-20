#include "WorldRenderer.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace raven;

WorldRenderer::WorldRenderer(sf::RenderWindow& renderWindow)
	: m_renderWindow(renderWindow)
{}

void WorldRenderer::DrawSphere(const glm::vec2& center, const sf::Color& color, float radius)
{
	static sf::CircleShape sphere(1);
	sphere.setOrigin(1, 1);
	sphere.setScale(1, 1);

	sphere.scale(radius, radius);
	sphere.setPosition(center.x, center.y);
	sphere.setFillColor(color);

	m_renderWindow.draw(sphere);
}

void WorldRenderer::DrawBox(const glm::vec2& center, const glm::vec2& extend, const sf::Color& color, float rotation)
{
	static sf::RectangleShape rect({1, 1});
	rect.setOrigin(1, 1);
	rect.setScale(1, 1);
	rect.setRotation(0);

	rect.scale(extend.x, extend.y);
	rect.setPosition(center.x, center.y);
	rect.setFillColor(color);
	rect.rotate(rotation);

	m_renderWindow.draw(rect);
}
