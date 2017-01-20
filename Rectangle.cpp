#include "stdafx.h"
#include "Rectangle.h"




CRectangle::CRectangle(Vec2 const& positon, Vec2 const& size)
	: m_position(positon)
	, m_size(size)
{
}

bool CRectangle::IsPointIntoRect(Vec2 const & point) const
{
	return (point.x >= m_position.x && point.x <= m_position.x + m_size.x) &&
					(point.y >= m_position.y && point.y <= m_position.y + m_size.y);
}

Vec2 CRectangle::GetSize() const
{
	return m_size;
}

Vec2 CRectangle::GetPosition() const
{
	return m_position;
}

void CRectangle::SetSize(Vec2 const & size)
{
	m_size = size;
}

void CRectangle::SecPosition(Vec2 const & position)
{
	m_position = position;
}

