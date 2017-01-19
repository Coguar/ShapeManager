#pragma once
//#include "Coords.h"

struct IRectangle
{
	virtual bool IsPointIntoRect(SCoords const& point)const = 0;
	virtual SSize GetSize()const = 0;
	virtual SCoords GetPosition()const = 0;
	virtual void SetSize(SSize const& size) = 0;
	virtual void SecPosition(SCoords const& position) = 0;
	virtual ~IRectangle() = default;
};