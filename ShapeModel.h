#pragma once
#include "Coords.h"
#include "ShapesTypes.h"

struct SModelShape
{
	SModelShape() = default;
	SModelShape(ShapeType type, Vec2 const& position, Vec2 const& size)
		: m_position(position)
		, m_size(size)
		, m_type(type)
	{};
	Vec2 m_position;
	Vec2 m_size;
	ShapeType m_type;
};