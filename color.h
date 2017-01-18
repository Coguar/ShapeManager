#pragma once

struct SColor
{
	SColor() = default;
	SColor(int red, int green, int blue, int alpha = 0)
		: r(red)
		, g(green)
		, b(blue)
		, a(alpha)
	{}
	
	int r = 0;
	int g = 0;
	int b = 0;
	int a = 0;
	
};