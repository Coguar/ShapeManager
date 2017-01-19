#pragma once
#include "AbstractShape.h"

class ÑSquare
	: public CAbstractShape
{
public:
	ÑSquare();
	~ÑSquare() = default;
	bool IsPointIntoShape(SCoords const& point)const override;
};

