#pragma once
#include "AbstractShape.h"

class �Square
	: public CAbstractShape
{
public:
	�Square();
	~�Square() = default;
	bool IsPointIntoShape(Vec2 const& point)const override;
};

