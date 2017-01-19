#pragma once
#include "Coords.h"

namespace shape
{
	const enum class Type
	{
		Circle = 0,
		Triangle,
		Rectangle,
	};
}

struct IShape
{
	virtual shape::Type GetType()const = 0;
	virtual bool IsPointIntoShape(SCoords const& point)const = 0;
	virtual ~IShape() = default;
};