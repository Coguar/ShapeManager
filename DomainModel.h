#pragma once
#include "ShapeModel.h"

class CDomainModel
{
public:
	CDomainModel();
	~CDomainModel();

	void AddShape(std::shared_ptr<SModelShape> const& shape);
	void AddShape(std::shared_ptr<SModelShape> const& shape, size_t position);
	void DeleteLastShape();
	void DeleteShapeByPosition(size_t position);

	void Clear();
	void SetNewShapeList(std::vector<std::shared_ptr<SModelShape>> const& shapes);

private:
	std::vector<std::shared_ptr<SModelShape>> m_shapes;
};

