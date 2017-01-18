#pragma once
#include "color.h"

struct IDrawable
{
	virtual void SetColor(SColor const& color) = 0;
	virtual SColor GetColor()const = 0;
	virtual ~IDrawable() = default;
};