#include "stdafx.h"
#include "Circle.h"
#include "Ellipse.h"

CCircle::CCircle()
	: CShape(ShapeType::Circle)
{
}

bool CCircle::IsPointIntoShape(Vec2 const & point) const
{
	auto position = GetPosition();
	Vec2 radius( GetSize().x / 2.0, GetSize().y / 2.0 );
	Vec2 origin(position.x + radius.x, position.y + radius.y);
	Vec2 pointLocalPos(point.x - origin.x, point.y - origin.y);
	
	return ((pow(pointLocalPos.x, 2) / pow(radius.x, 2)) + (pow(pointLocalPos.y, 2) / pow(radius.y, 2))) <= 1;
}

void CCircle::Draw(sf::RenderTarget * window, CTextureCache * cache)
{
	if (window != nullptr)
	{
		auto size = GetSize();
		CEllipse ellipse({ float(size.x / 2.0), float(size.y / 2.0) });
		ellipse.setPosition(sf::Vector2f(float(GetPosition().x), float(GetPosition().y)));
		auto color = GetColor();
		ellipse.setFillColor(sf::Color(sf::Uint8(color.r), sf::Uint8(color.g), sf::Uint8(color.b), sf::Uint8(color.a)));
		ellipse.setOutlineThickness(SHAPE_OUTLINE_SIZE);
		ellipse.setOutlineColor(sf::Color::Black);
		window->draw(ellipse);
	}
}
