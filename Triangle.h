#pragma once
#include "AbstractShape.h"
class CTriangle :
	public CAbstractShape
{
public:
	CTriangle();
	~CTriangle() = default;
	bool IsPointIntoShape(Vec2 const& point)const override;

private:
	bool IsPointInsideTriangle(Vec2 const& point1, Vec2 const& point2, Vec2 const& point3) const;
};

