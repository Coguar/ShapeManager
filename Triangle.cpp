#include "stdafx.h"
#include "Triangle.h"

namespace
{

}

CTriangle::CTriangle()
	: CShape(ShapeType::Triangle)
{
}

bool CTriangle::IsPointIntoShape(Vec2 const & point) const
{
	Vec2 bottomRightPoint(GetPosition().x + GetSize().x, GetPosition().y + GetSize().y);
	return IsPointInsideTriangle(GetPosition(), bottomRightPoint, point);
}

void CTriangle::Draw(sf::RenderTarget * window, CTextureCache * cache)
{
	if (window != nullptr)
	{
		auto rect = GetBoundingRect();

		sf::ConvexShape convex(3);
		convex.setPoint(0, { float(rect.position.x), float(rect.position.y + rect.size.y) });
		convex.setPoint(1, { float(rect.position.x + rect.size.x / 2.f), float(rect.position.y) });
		convex.setPoint(2, { float(rect.position.x + rect.size.x), float(rect.position.y + rect.size.y) });
		auto color = GetColor();
		convex.setFillColor(sf::Color(sf::Uint8(color.r), sf::Uint8(color.g), sf::Uint8(color.b), sf::Uint8(color.a)));
		convex.setOutlineThickness(SHAPE_OUTLINE_SIZE);
		convex.setOutlineColor(sf::Color::Black);
		window->draw(convex);
	}
}

bool CTriangle::IsPointInsideTriangle(Vec2 const& topLeft, Vec2 const& bottomRight, Vec2 const& point) const
{
	return (point.y > 2 * (topLeft.y - bottomRight.y) * (point.x - topLeft.x) / (bottomRight.x - topLeft.x) + bottomRight.y
		&& point.y > 2 * (topLeft.y - bottomRight.y) * (point.x - bottomRight.x) / (topLeft.x - bottomRight.x) + bottomRight.y && point.y < bottomRight.y);
}