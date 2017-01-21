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
		m_isMoved = true;
		return true;
	}
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
		auto oldPosition = GetPosition();
		SetPosition({ double(event.x) + m_offset.x, double(event.y) + m_offset.y });
		auto position = GetPosition();
		auto size = GetSize();
		if (!(position.x >= m_allowableArea.position.x && position.x + size.x <= m_allowableArea.position.x + m_allowableArea.size.x))
		{
			position.x = oldPosition.x;
		}
		if (!(position.y >= m_allowableArea.position.y && position.y + size.y <= m_allowableArea.position.y + m_allowableArea.size.y))
		{
			position.y = oldPosition.y;
		}
		SetPosition(position);
		return true;
	}
	return false;
}

bool CShape::IsMooved() const
{
	return m_isMoved;
}

void CShape::SetAllowableArea(CBoundingRect const & rect)
{
	m_allowableArea = rect;
}

CBoundingRect const & CShape::GetAllowableArea() const
{
	return m_allowableArea;
}
