#pragma once
#include "AbstractShape.h"

class �Square
	: public CAbstractShape
{
public:
	�Square();
	~�Square() = default;
	bool IsPointIntoShape(SCoords const& point)const override;
};

