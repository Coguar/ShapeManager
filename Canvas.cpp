#include "stdafx.h"
#include "Canvas.h"
#include "FileReader.h"

CCanvas::CCanvas()
	: m_size(CANVAS_SIZE)
{
}


CCanvas::~CCanvas()
{
}

void CCanvas::AddShape(std::shared_ptr<SModelShape> const & shape)
{
	m_shapes.push_back(shape);
	m_onShapeAdded(shape, m_shapes.size() - 1);
}

void CCanvas::AddShape(std::shared_ptr<SModelShape> const & shape, size_t position)
{
	m_shapes.insert(m_shapes.begin() + position, shape);
	m_onShapeAdded(shape, position);
}

std::shared_ptr<SModelShape> CCanvas::DeleteLastShape()
{
	auto shape = m_shapes.back();
	m_onShapeDelete(m_shapes.size() - 1);
	m_shapes.pop_back();
	return shape;
}

std::shared_ptr<SModelShape> CCanvas::DeleteShapeByPosition(size_t position)
{
	auto shape = m_shapes[position];
	m_shapes.erase(m_shapes.begin() + position);
	m_onShapeDelete(position);
	return shape;
}

void CCanvas::Clear()
{
	m_shapes.clear();
	m_onShapeListClear();
}

void CCanvas::SetNewShapeList(std::vector<std::shared_ptr<SModelShape>> const & shapes)
{
	Clear();
	for (auto &shape : shapes)
	{
		AddShape(shape);
	}
}

std::vector<std::shared_ptr<SModelShape>> const & CCanvas::GetData() const
{
	return m_shapes;
}

Vec2 CCanvas::GetSize() const
{
	return m_size;
}

void CCanvas::DoOnShapeAdd(std::function<void(std::shared_ptr<SModelShape>, size_t)> const & action)
{
	m_onShapeAdded.connect(action);
}

void CCanvas::DoOnShapeDelete(std::function<void(size_t)> const & action)
{
	m_onShapeDelete.connect(action);
}

void CCanvas::DoOnShapesClear(std::function<void()> const & action)
{
	m_onShapeListClear.connect(action);
}
