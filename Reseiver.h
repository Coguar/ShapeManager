#pragma once
#include "AbstractShape.h"
#include <memory>

using ShapePtr = std::shared_ptr<CShape>;

struct IReseiver
{
	virtual void AddShape(ShapePtr const& shape) = 0;
	virtual void DeleteShape(ShapePtr const& shape, int num) = 0;
	virtual void MoveShape(ShapePtr const& shape, Vec2 const& newPos) = 0;
	virtual void ResizeShape(ShapePtr const& shape, Vec2 const& oldSize) = 0;

	virtual void Redo() = 0;
	virtual void Undo() = 0;
	virtual ~IReseiver() = default;
};