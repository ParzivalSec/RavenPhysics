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

void WorldRenderer::DrawBox(const glm::vec2& center, const glm::vec2& extend, const sf::Color& color, float rotation, bool wireFrame)
{
	static sf::RectangleShape rect({ 1, 1 });
	rect.setOrigin(0.5, 0.5);
	rect.setScale(1, 1);
	rect.setRotation(0);

	rect.scale(extend.x, extend.y);
	rect.setPosition(center.x, center.y);
	rect.rotate(rotation);

	if (wireFrame)
	{
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(color);
		rect.setOutlineThickness(1.0f / extend.x);
	}
	else
	{
		rect.setFillColor(color);
		rect.setOutlineColor(sf::Color::Transparent);
		rect.setOutlineThickness(0.0f);
	}

	m_renderWindow.draw(rect);
}

void WorldRenderer::DrawBox(const glm::vec2& pointA, const glm::vec2& pointB, const glm::vec2& pointC, 
	const glm::vec2& pointD, const sf::Color& color, bool wireFrame)
{
	static sf::VertexArray vertexArray;
	static sf::Vertex vertex;

	vertexArray.clear();

	vertex.position = { pointA.x, pointA.y };
	vertex.color = color;
	vertexArray.append(vertex);

	vertex.position = { pointB.x, pointB.y };
	vertex.color = color;
	vertexArray.append(vertex);

	vertex.position = { pointC.x, pointC.y };
	vertex.color = color;
	vertexArray.append(vertex);

	vertex.position = { pointC.x, pointC.y };
	vertex.color = color;
	vertexArray.append(vertex);

	vertex.position = { pointD.x, pointD.y };
	vertex.color = color;
	vertexArray.append(vertex);

	vertex.position = { pointA.x, pointA.y };
	vertex.color = color;
	vertexArray.append(vertex);

	if (wireFrame)
	{
		vertexArray.setPrimitiveType(sf::LineStrip);
	}
	else
	{
		vertexArray.setPrimitiveType(sf::Triangles);
	}

	m_renderWindow.draw(vertexArray);
}

void WorldRenderer::DrawLine(const glm::vec2& pointA, const glm::vec2& pointB, const sf::Color& color)
{
	static sf::VertexArray vertexArray(sf::Lines);
	static sf::Vertex vertex;

	vertexArray.clear();

	vertex.position = { pointA.x, pointA.y };
	vertex.color = color;
	vertexArray.append(vertex);

	vertex.position = { pointB.x, pointB.y };
	vertex.color = color;
	vertexArray.append(vertex);

	m_renderWindow.draw(vertexArray);
}
