#pragma once
#include "AbstractShape.h"
class CCircle :
	public CAbstractShape
{
public:
	CCircle();
	~CCircle() = default;
	bool IsPointIntoShape(SCoords const& point)const override;
};

