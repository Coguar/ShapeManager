#include "stdafx.h"
#include "ÑSquare.h"


ÑSquare::ÑSquare()
	:CAbstractShape(shape::Type::Rectangle)
{
}

bool ÑSquare::IsPointIntoShape(SCoords const & point) const
{
	return IsPointIntoRect(point);
}
