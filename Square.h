#pragma once
#include "AbstractShape.h"

class ÑSquare
	: public CShape
{
public:
	ÑSquare();
	~ÑSquare() = default;
	bool IsPointIntoShape(Vec2 const& point)const override;
};

