#pragma once
#include "Canvas.h"

struct IView
{
	virtual void Draw(CLayer * layer) = 0;
	virtual void DrawShapes(CCanvas * canvas) = 0;
	virtual ~IView() = default;
};