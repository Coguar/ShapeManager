#pragma once
#include "Coords.h"

class CBoundingRect
{
public:
	CBoundingRect() = default;
	CBoundingRect(Vec2 const& positon, Vec2 const& size);
	~CBoundingRect() = default;

	bool IsPointInRect(Vec2 const& point)const;

	Vec2 position;
	Vec2 size;
};

