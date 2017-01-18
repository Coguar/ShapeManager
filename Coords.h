#pragma once

struct SCoords
{
	SCoords() = default;
	SCoords(double xPos, double yPos)
		: x(xPos)
		, y(yPos)
	{}
	double x;
	double y;
};

typedef SCoords SSize;