#pragma once
#include "SelectFrame.h"

struct IView
{
	virtual void Draw(CParentLayer * layer) = 0;
	virtual void DrawShapes(std::vector<std::shared_ptr<CShape>> const& shapes) = 0;
	virtual void DrawSelectFrame(std::shared_ptr<CSelectFrame> const& frame) = 0;
	virtual ~IView() = default;
};