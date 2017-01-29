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
	m_events.push_back(DomEvent(DomEventType::Add, m_shapes.size() - 1, m_shapes.back()));
	DataChanged();
}

void CDomainModel::AddShape(std::shared_ptr<SModelShape> const & shape, size_t position)
{
	m_shapes.insert(m_shapes.begin() + position, shape);
	m_events.push_back(DomEvent(DomEventType::Add, position, m_shapes[position]));
	DataChanged();
}

std::shared_ptr<SModelShape> CDomainModel::DeleteLastShape()
{
	auto shape = m_shapes.back();
	m_events.push_back(DomEvent(DomEventType::Del, m_shapes.size() - 1, m_shapes.back()));
	m_shapes.pop_back();
	DataChanged();
	return shape;
}

std::shared_ptr<SModelShape> CDomainModel::DeleteShapeByPosition(size_t position)
{
	auto shape = m_shapes[position];
	m_events.push_back(DomEvent(DomEventType::Del, position, m_shapes[position]));
	m_shapes.erase(m_shapes.begin() + position);
	DataChanged();
	return shape;
}

void CDomainModel::ChangeShapeSettings(size_t shapeNum, Vec2 const & pos, Vec2 const & size)
{
	m_shapes[shapeNum]->m_position = pos;
	m_shapes[shapeNum]->m_size = size;
	m_events.push_back(DomEvent(DomEventType::Change, shapeNum, m_shapes[shapeNum]));
	DataChanged();
}

void CDomainModel::Clear()
{
	m_shapes.clear();
	m_events.push_back(DomEvent(DomEventType::Clear, 0, nullptr));
	DataChanged();
}

void CDomainModel::SetNewShapeList(std::vector<std::shared_ptr<SModelShape>> const & shapes)
{
	Clear();
	for (auto &shape : shapes)
	{
		m_shapes.push_back(shape);
		m_events.push_back(DomEvent(DomEventType::Add, m_shapes.size() - 1, shape));
	}
	DataChanged();
}

void CDomainModel::DataSaved()
{
	m_events.push_back(DomEvent(DomEventType::Saved, 0, nullptr));
	DataChanged();
}

void CDomainModel::DataChanged()
{
	NotifyObservers();
	m_events.clear();
}

std::vector<std::shared_ptr<SModelShape>> const & CDomainModel::GetData() const
{
	return m_shapes;
}

DataType CDomainModel::GetChangedData() const
{
	return m_events;
}
