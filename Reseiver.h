#pragma once
#include <memory>

class CShape;

using ShapePtr = std::shared_ptr<CShape>;

struct IReseiver
{
	virtual void Redo() = 0;
	virtual void Undo() = 0;

	virtual void Clear() = 0;
	virtual ~IReseiver() = default;
};