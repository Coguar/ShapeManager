#include "stdafx.h"
#include "Square.h"


ÑSquare::ÑSquare()
	:CShape(ShapeType::Rectangle)
{
}

bool ÑSquare::IsPointIntoShape(Vec2 const & point) const
{
	return GetBoundingRect().IsPointInRect(point);
}

void ÑSquare::Draw(sf::RenderTarget * window, CTextureCache * cache)
{
	if (window != nullptr)
	{
		auto rect = GetBoundingRect();
		sf::RectangleShape rectangle({ float(rect.size.x), float(rect.size.y) });
		rectangle.setPosition({ float(rect.position.x), float(rect.position.y) });
		auto color = GetColor();
		rectangle.setFillColor(sf::Color(sf::Uint8(color.r), sf::Uint8(color.g), sf::Uint8(color.b), sf::Uint8(color.a)));
		rectangle.setOutlineThickness(SHAPE_OUTLINE_SIZE);
		rectangle.setOutlineColor(sf::Color::Black);
		window->draw(rectangle);
	}
}
