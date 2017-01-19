#pragma once
#include "AbstractShape.h"
#include <memory>
#include <vector>
#include <SFML\Window.hpp>

struct ICanvas
{
	virtual std::vector<std::shared_ptr<CAbstractShape>> const& GetShapes()const = 0;
	virtual std::shared_ptr<CAbstractShape> CreateShape(shape::Type type) = 0;
	virtual ~ICanvas() = default;
};