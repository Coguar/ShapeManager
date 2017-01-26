#include "stdafx.h"
#include "DomainModel.h"


CDomainModel::CDomainModel()
{
}


CDomainModel::~CDomainModel()
{
}

void CDomainModel::AddShape(std::shared_ptr<SModelShape> const & shape)
{
	m_shapes.push_back(shape);
}

void CDomainModel::AddShape(std::shared_ptr<SModelShape> const & shape, size_t position)
{
	m_shapes.insert(m_shapes.begin() + position, shape);
}

void CDomainModel::DeleteLastShape()
{
	m_shapes.pop_back();
}

void CDomainModel::DeleteShapeByPosition(size_t position)
{
	m_shapes.erase(m_shapes.begin() + position);
}

void CDomainModel::Clear()
{
	m_shapes.clear();
}

void CDomainModel::SetNewShapeList(std::vector<std::shared_ptr<SModelShape>> const & shapes)
{
	Clear();
	for (auto &shape : shapes)
	{
		m_shapes.push_back(shape);
	}
}
