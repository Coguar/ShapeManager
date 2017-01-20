#include "stdafx.h"
#include "Rectangle.h"




CBoundingRect::CBoundingRect(Vec2 const& positon, Vec2 const& size)
	: position(positon)
	, size(size)
{
}

bool CBoundingRect::IsPointInRect(Vec2 const & point) const
{
	return (point.x >= position.x && point.x <= position.x + size.x) &&
					(point.y >= position.y && point.y <= position.y + size.y);
}

