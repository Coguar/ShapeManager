#include "stdafx.h"
#include "AbstractShape.h"

CShape::CShape(ShapeType type)
	: m_type(type)
{}

ShapeType CShape::GetType() const
{
	return m_type;
}

bool CShape::IsPointIntoShape(Vec2 const & point) const
{
	return false;
}

bool CShape::OnMousePressed(sf::Event::MouseButtonEvent const & event)
{
	if (IsPointIntoShape({ float(event.x), float(event.y) }))
	{
		return true;
	}
	return false;
}

bool CShape::OnMouseReleased(sf::Event::MouseButtonEvent const & event)
{
	return false;
}

bool CShape::OnMouseMoved(sf::Event::MouseMoveEvent const & event)
{
	return false;
}
