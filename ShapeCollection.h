#pragma once
#include <memory>

class SModelShape;

struct IShapeCollection
{
	virtual void AddShape(std::shared_ptr<SModelShape> const& shape) = 0;
	virtual void AddShape(std::shared_ptr<SModelShape> const& shape, size_t position) = 0;
	virtual std::shared_ptr<SModelShape> DeleteLastShape() = 0;
	virtual std::shared_ptr<SModelShape> DeleteShapeByPosition(size_t position) = 0;
	virtual ~IShapeCollection() = default;
};