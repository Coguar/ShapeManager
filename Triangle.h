#pragma once
#include "AbstractShape.h"
class CTriangle :
	public CAbstractShape
{
public:
	CTriangle();
	~CTriangle() = default;
	bool IsPointIntoShape(SCoords const& point)const override;

private:
	bool IsPointInsideTriangle(SCoords const& point1, SCoords const& point2, SCoords const& point3) const;
};

