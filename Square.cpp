#include "stdafx.h"
#include "Square.h"


ÑSquare::ÑSquare()
	:CAbstractShape(ShapeType::Rectangle)
{
}

bool ÑSquare::IsPointIntoShape(Vec2 const & point) const
{
	return IsPointIntoRect(point);
}
