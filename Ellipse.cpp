#include "stdafx.h"
#include "Ellipse.h"


CEllipse::CEllipse(const sf::Vector2f & radius, unsigned int pointsCount)
	: m_radius(radius)
	, m_pointsCount(pointsCount)
{
	update();
}


void CEllipse::setRadius(const sf::Vector2f& radius)
{
	m_radius = radius;
	update();
}

const sf::Vector2f& CEllipse::getRadius() const
{
	return m_radius;
}

unsigned int CEllipse::getPointCount() const
{
	return m_pointsCount;
}

sf::Vector2f CEllipse::getPoint(unsigned int index) const
{
	float angle = float(index * 2.0 * M_PI / getPointCount() - M_PI / 2.0);
	float x = std::cos(angle) * m_radius.x;
	float y = std::sin(angle) * m_radius.y;

	return sf::Vector2f(m_radius.x + x, m_radius.y + y);
}
