#include "stdafx.h"
#include "Square.h"


�Square::�Square()
	:CAbstractShape(ShapeType::Rectangle)
{
}

bool �Square::IsPointIntoShape(Vec2 const & point) const
{
	return IsPointIntoRect(point);
}
