#include "stdafx.h"
#include "Circle.h"


CCircle::CCircle()
	: CAbstractShape(ShapeType::Circle)
{
}

bool CCircle::IsPointIntoShape(Vec2 const & point) const
{
	auto position = GetPosition();
	Vec2 radius( GetSize().x / 2.0, GetSize().y / 2.0 );
	Vec2 origin(position.x + radius.x, position.y + radius.y);
	Vec2 pointLockalPos(point.x - origin.x, point.y - origin.y);
	
	return ((pow(pointLockalPos.x, 2) / pow(radius.x, 2)) + (pow(pointLockalPos.y, 2) / pow(radius.y, 2))) <= 1;
}
