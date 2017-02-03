#include "stdafx.h"
#include "DomainModel.h"
#include "FileReader.h"

CDomainModel::CDomainModel()
{
}


CDomainModel::~CDomainModel()
{
}

void CDomainModel::AddShape(std::shared_ptr<SModelShape> const & shape)
{
	m_shapes.push_back(shape);
	m_onShapeAdded(shape, m_shapes.size() - 1);
	m_onDataChange();
}

void CDomainModel::AddShape(std::shared_ptr<SModelShape> const & shape, size_t position)
{
	m_shapes.insert(m_shapes.begin() + position, shape);
	m_onShapeAdded(shape, position);
	m_onDataChange();
}

std::shared_ptr<SModelShape> CDomainModel::DeleteLastShape()
{
	auto shape = m_shapes.back();
	m_onShapeDelete(m_shapes.size() - 1);
	m_shapes.pop_back();
	m_onDataChange();
	return shape;
}

std::shared_ptr<SModelShape> CDomainModel::DeleteShapeByPosition(size_t position)
{
	auto shape = m_shapes[position];
	m_shapes.erase(m_shapes.begin() + position);
	m_onShapeDelete(position);
	m_onDataChange();
	return shape;
}

void CDomainModel::ChangeShapeSettings(size_t shapeNum, Vec2 const & pos, Vec2 const & size)
{
	m_shapes[shapeNum]->SetRect(pos, size);
	m_onDataChange();
}

void CDomainModel::Clear()
{
	m_shapes.clear();
	m_onShapeListClear();
	m_onDataChange();
}

void CDomainModel::SetNewShapeList(std::vector<std::shared_ptr<SModelShape>> const & shapes)
{
	Clear();
	for (auto &shape : shapes)
	{
		AddShape(shape);
	}
	m_onDataChange();
}

void CDomainModel::DataSaved()
{
	m_onDataSaved();
}

std::vector<std::shared_ptr<SModelShape>> const & CDomainModel::GetData() const
{
	return m_shapes;
}

void CDomainModel::DoOnShapeAdd(std::function<void(std::shared_ptr<SModelShape>const&shape, size_t number)> const & action)
{
	m_onShapeAdded.connect(action);
}

void CDomainModel::DoOnShapeDelete(std::function<void(size_t number)> const & action)
{
	m_onShapeDelete.connect(action);
}

void CDomainModel::DoOnShapesClear(std::function<void()> const & action)
{
	m_onShapeListClear.connect(action);
}

void CDomainModel::DoOnDataSaved(std::function<void()> const & action)
{
	m_onDataSaved.connect(action);
}

void CDomainModel::DoOndataChanged(std::function<void()> const & action)
{
	m_onDataChange.connect(action);
}

