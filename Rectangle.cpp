#include "stdafx.h"
#include "Rectangle.h"




CRectangle::CRectangle(SCoords const& positon, SSize const& size)
	: m_position(positon)
	, m_size(size)
{
}

bool CRectangle::IsPointIntoRect(SCoords const & point) const
{
	return (point.x >= m_position.x && point.x <= m_position.x + m_size.x) &&
					(point.y >= m_position.y && point.y <= m_position.y + m_size.y);
}

SSize CRectangle::GetSize() const
{
	return m_size;
}

SCoords CRectangle::GetPosition() const
{
	return m_position;
}

void CRectangle::SetSize(SSize const & size)
{
	m_size = size;
}

void CRectangle::SecPosition(SCoords const & position)
{
	m_position = position;
}

