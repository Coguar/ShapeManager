#pragma once
#include "AbstractShape.h"
#include <memory>
#include <vector>
#include <SFML\Window.hpp>

struct ICanvas
{
	virtual std::vector<std::shared_ptr<CShape>> const& GetShapes()const = 0;
	virtual std::shared_ptr<CShape> CreateShape(ShapeType type) = 0;
	virtual ~ICanvas() = default;
};