#include "stdafx.h"
#include "Picture.h"
#include "Canvas.h"
#include "FileReader.h"

using namespace signal;

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

void CCanvas::MoveShapeUp(size_t position)
{
	if (position < m_shapes.size() - 1)
	{
		auto tempShape = m_shapes[position + 1];
		m_shapes[position + 1] = m_shapes[position];
		m_shapes[position] = tempShape;
		m_onMoveShapesLayer(position, true);
	}
}

void CCanvas::MoveShapeDown(size_t position)
{
	if (position > 0)
	{
		auto tempShape = m_shapes[position - 1];
		m_shapes[position - 1] = m_shapes[position];
		m_shapes[position] = tempShape;
		m_onMoveShapesLayer(position, false);
	}
}

void CCanvas::Clear()
{
	for (auto &shape : m_shapes)
	{
		if (shape->GetType() == ShapeType::Picture)
		{
			m_resHasBecomeUnusable(dynamic_cast<CPicture*>(shape.get())->GetTexturePath());
		}
	}
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

Connection CCanvas::DoOnShapeAdd(std::function<void(std::shared_ptr<SModelShape>, size_t)> const & action)
{
	return m_onShapeAdded.connect(action);
}

Connection CCanvas::DoOnShapeDelete(std::function<void(size_t)> const & action)
{
	return m_onShapeDelete.connect(action);
}

Connection CCanvas::DoOnShapesClear(std::function<void()> const & action)
{
	return m_onShapeListClear.connect(action);
}

signal::Connection CCanvas::DoOnShapesLayerMove(std::function<void(size_t, bool)> const & action)
{
	return m_onMoveShapesLayer.connect(action);
}

signal::Connection CCanvas::DoOnResourceBecomingUnusable(std::function<void(std::string)> const & action)
{
	return m_resHasBecomeUnusable.connect(action);
}
