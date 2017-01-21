#pragma once
#include "color.h"
#include "Rectangle.h"

namespace color
{
	static const SColor PURPLE = SColor(255, 0, 255, 255);
	static const SColor YELLOW = SColor(255, 255, 0, 255);
	static const SColor GREEN = SColor(0, 255, 0, 255);
	static const SColor BLUE = SColor(0, 0, 255, 255);
	static const SColor WHITE = SColor(255, 255, 255, 255);
	static const SColor Black;

	static const SColor SHAPE_COLOR = PURPLE;
	static const SColor DRAG_POINT_COLOR = SColor(255, 0, 0, 128);
}

static const Vec2 INITIALIZATION_SHAPE_SIZE = { 40, 40 };
static const Vec2 DRAG_POINT_SIZE = { 10, 10 };

static const double MAX_SHAPE_SIZE = 140.0;
static const double MIN_SHAPE_SIZE = 30.0;
static const double DEFAULT_TOOLBAR_ELEMENT_OFFSET = 10.0;

static const float SHAPE_OUTLINE_SIZE = 2.f;

static const unsigned int DEFOULT_ELLIPSE_POINTS_COUNT = 30;