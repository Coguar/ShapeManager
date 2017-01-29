#pragma once
#include <string>
#include "color.h"
#include "Rectangle.h"

namespace color
{
	static const SColor PURPLE = SColor(255, 0, 255, 255);
	static const SColor YELLOW = SColor(255, 255, 0, 255);
	static const SColor GREEN = SColor(0, 255, 0, 255);
	static const SColor BLUE = SColor(0, 0, 255, 255);
	static const SColor WHITE = SColor(255, 255, 255, 255);
	static const SColor LITE_GRAY = SColor(200, 200, 200, 255);
	static const SColor BLACK;

	static const SColor SHAPE_COLOR = PURPLE;
	static const SColor DRAG_POINT_COLOR = SColor(255, 0, 0, 128);
}
static const Vec2 MAIN_WINDOW_SIZE = { 800, 600 };

static const Vec2 INITIALIZATION_SHAPE_SIZE = { 40, 40 };
static const Vec2 DRAG_POINT_SIZE = { 10, 10 };
static const Vec2 DEFAULT_BUTTONN_SIZE = { 80.0, 80.0 };

static const Vec2 CANVAS_POSITION = { 5, 105 };
static const Vec2 CANVAS_SIZE = { 790, 490 };

static const Vec2 TOOLBAR_POSITION = { 0, 0 };
static const Vec2 TOOLBAR_SIZE = { 800, 100 };

static const double MAX_SHAPE_SIZE = 200.0;
static const double MIN_SHAPE_SIZE = 20.0;
static const double DEFAULT_TOOLBAR_ELEMENT_OFFSET = 10.0;

static const float SHAPE_OUTLINE_SIZE = 2.f;

static const unsigned int DEFOULT_ELLIPSE_POINTS_COUNT = 30;

static const std::string CIRCLE_PATH = "./res/circle.png";
static const std::string RECTANGLE_PATH = "./res/square.png";
static const std::string TRIANGLE_PATH = "./res/triangle.png";
static const std::string REDO_PATH = "./res/redo.png";
static const std::string UNDO_PATH = "./res/undo.png";
static const std::string OPEN_PATH = "./res/open.png";
static const std::string SAVE_PATH = "./res/save.png";
static const std::string NEW_PATH = "./res/new.png";

static const std::string SAVE_MSG = "Current data will be lost! Would you like to save them?";