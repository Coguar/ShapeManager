#pragma once
#include "Coords.h"

const enum class ShapeType
{
	Circle = 0,
	Triangle,
	Rectangle,
};

struct IShape
{
	virtual ShapeType GetType()const = 0;
	virtual bool IsPointIntoShape(Vec2 const& point)const = 0;
	virtual ~IShape() = default;
};