#pragma once

struct Vec2
{
	Vec2() = default;
	Vec2(double x, double y)
		: x(x)
		, y(y)
	{}
	double x = 0.0;
	double y = 0.0;

	bool operator==(Vec2 const& right);
};