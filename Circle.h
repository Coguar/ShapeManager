#pragma once
#include "AbstractShape.h"
class CCircle :
	public CAbstractShape
{
public:
	CCircle();
	~CCircle() = default;
	bool IsPointIntoShape(Vec2 const& point)const override;
};

