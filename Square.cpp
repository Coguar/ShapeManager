#include "stdafx.h"
#include "Square.h"


ÑSquare::ÑSquare()
	:CAbstractShape(shape::Type::Rectangle)
{
}

bool ÑSquare::IsPointIntoShape(SCoords const & point) const
{
	return IsPointIntoRect(point);
}
