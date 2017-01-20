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
	if (IsPointIntoShape({ double(event.x), double(event.y) }))
	{
		auto position = GetBoundingRect().position;
		m_offset = { position.x - double(event.x), position.y - double(event.y)};
		m_isSelected = true;
		m_isMoved = true;
		return true;
	}
	m_isSelected = false;
	return false;
}

bool CShape::OnMouseReleased(sf::Event::MouseButtonEvent const & event)
{
	m_isMoved = false;
	return false;
}

bool CShape::OnMouseMoved(sf::Event::MouseMoveEvent const & event)
{
	if (m_isMoved)
	{
		SetPosition({ double(event.x) + m_offset.x, double(event.y) + m_offset.y });
		return true;
	}
	return false;
}

bool CShape::IsMooved() const
{
	return m_isMoved;
}
