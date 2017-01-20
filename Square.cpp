#include "stdafx.h"
#include "Square.h"


�Square::�Square()
	:CShape(ShapeType::Rectangle)
{
}

bool �Square::IsPointIntoShape(Vec2 const & point) const
{
	return GetBoundingRect().IsPointInRect(point);
}
