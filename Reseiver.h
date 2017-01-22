#pragma once
#include <memory>

class CShape;

using ShapePtr = std::shared_ptr<CShape>;

struct IReseiver
{
	virtual void AddShape(ShapePtr const& shape) = 0;
	virtual void DeleteShape(ShapePtr const& shape, int num) = 0;
	virtual void ChangeRect(ShapePtr const& shape, CBoundingRect const& rect) = 0;

	virtual void Redo() = 0;
	virtual void Undo() = 0;
	virtual ~IReseiver() = default;
};