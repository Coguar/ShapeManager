#include "stdafx.h"
#include "Circle.h"


CCircle::CCircle()
	: CAbstractShape(shape::Type::Circle)
{
}

bool CCircle::IsPointIntoShape(SCoords const & point) const
{
	auto position = GetPosition();
	SSize radius( GetSize().x / 2.0, GetSize().y / 2.0 );
	SCoords origin(position.x + radius.x, position.y + radius.y);
	SCoords pointLockalPos(point.x - origin.x, point.y - origin.y);
	
	return ((pow(pointLockalPos.x, 2) / pow(radius.x, 2)) + (pow(pointLockalPos.y, 2) / pow(radius.y, 2))) <= 1;
}
