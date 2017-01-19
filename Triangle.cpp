#include "stdafx.h"
#include "Triangle.h"

namespace
{

}

CTriangle::CTriangle()
	: CAbstractShape(shape::Type::Triangle)
{
}

bool CTriangle::IsPointIntoShape(SCoords const & point) const
{
	SCoords topLeftPoint(GetPosition().x, GetPosition().y + GetSize().y);
	SCoords bottomRightPoint(GetPosition().x + GetSize().x, GetPosition().y);
	return IsPointInsideTriangle(topLeftPoint, bottomRightPoint, point);
}

bool CTriangle::IsPointInsideTriangle(SCoords const& topLeft, SCoords const& bottomRight, SCoords const& point) const
{
	return (point.y > 2 * (topLeft.y - bottomRight.y) * (point.x - topLeft.x) / (bottomRight.x - topLeft.x) + bottomRight.y
		&& point.y > 2 * (topLeft.y - bottomRight.y) * (point.x - bottomRight.x) / (topLeft.x - bottomRight.x) + bottomRight.y && point.y < bottomRight.y);
}
