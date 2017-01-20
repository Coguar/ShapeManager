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
