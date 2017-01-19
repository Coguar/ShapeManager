#include "stdafx.h"
#include "AbstractShape.h"

CAbstractShape::CAbstractShape(shape::Type type)
	: m_type(type)
{}

shape::Type CAbstractShape::GetType() const
{
	return m_type;
}

bool CAbstractShape::IsPointIntoShape(SCoords const & point) const
{
	return false;
}

bool CAbstractShape::OnMousePressed(sf::Event::MouseButtonEvent const & event)
{
	if (IsPointIntoShape({ float(event.x), float(event.y) }))
	{
		return true;
	}
	return false;
}

bool CAbstractShape::OnMouseReleased(sf::Event::MouseButtonEvent const & event)
{
	return false;
}

bool CAbstractShape::OnMouseMoved(sf::Event::MouseMoveEvent const & event)
{
	return false;
}
