#include "stdafx.h"
#include "ShapeModel.h"

SModelShape::SModelShape(ShapeType type, Vec2 const & position, Vec2 const & size)
	: m_position(position)
	, m_size(size)
	, m_type(type)
{}

void SModelShape::SetRect(Vec2 const & pos, Vec2 const & size)
{
	m_position = pos;
	m_size = size;
	m_OnRectChange(m_position, m_size);
}

ShapeType SModelShape::GetType() const
{
	return m_type;
}

Vec2 SModelShape::GetPosition() const
{
	return m_position;
}

Vec2 SModelShape::GetSize() const
{
	return m_size;
}

void SModelShape::DoOnRectChanged(std::function<void(Vec2, Vec2)> const & action)
{
	m_OnRectChange.connect(action);
}

