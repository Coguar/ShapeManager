#include "stdafx.h"
#include "Square.h"


�Square::�Square()
	:CAbstractShape(shape::Type::Rectangle)
{
}

bool �Square::IsPointIntoShape(SCoords const & point) const
{
	return IsPointIntoRect(point);
}
