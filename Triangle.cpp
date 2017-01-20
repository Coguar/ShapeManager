#include "stdafx.h"
#include "Triangle.h"

namespace
{

}

CTriangle::CTriangle()
	: CShape(ShapeType::Triangle)
{
}

bool CTriangle::IsPointIntoShape(Vec2 const & point) const
{
	Vec2 topLeftPoint(GetPosition().x, GetPosition().y + GetSize().y);
	Vec2 bottomRightPoint(GetPosition().x + GetSize().x, GetPosition().y);
	return IsPointInsideTriangle(topLeftPoint, bottomRightPoint, point);
}

bool CTriangle::IsPointInsideTriangle(Vec2 const& topLeft, Vec2 const& bottomRight, Vec2 const& point) const
{
	return (point.y > 2 * (topLeft.y - bottomRight.y) * (point.x - topLeft.x) / (bottomRight.x - topLeft.x) + bottomRight.y
		&& point.y > 2 * (topLeft.y - bottomRight.y) * (point.x - bottomRight.x) / (topLeft.x - bottomRight.x) + bottomRight.y && point.y < bottomRight.y);
}
