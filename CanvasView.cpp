#include "stdafx.h"
#include "Circle.h"
#include "Triangle.h"
#include "Square.h"
#include "Reseiver.h"
#include "ShapeModel.h"
#include "ShapePresenter.h"
#include "CanvasView.h"


CCanvasView::CCanvasView()
{
	m_frame = std::make_shared<CSelectFrame>();
}


CCanvasView::~CCanvasView()
{
}

bool CCanvasView::OnEvent(sf::Event const & event)
{
	if (m_frame->OnEvent(event))
	{
		return true;
	}
	CParentLayer::OnEvent(event);
	for (int i = int(m_shapes.size()) - 1; i >= 0; --i)
	{
		if (m_shapes[i]->OnEvent(event))
		{
			m_frame->SetTarget(m_shapes[i], i);
			m_targetShapePosition = i;
			ShapeChangeRectEvent(m_shapes[i], event);
			return true;
		}
	}
	return false;
}

bool CCanvasView::OnMousePressed(sf::Event::MouseButtonEvent const & event)
{
	if (GetBoundingRect().IsPointInRect({ double(event.x), double(event.y) }))
	{
		m_frame->ResetTargget();
		return true;
	}
	return false;
}

std::shared_ptr<CSelectFrame> const & CCanvasView::GetFSelectFrame() const
{
	return m_frame;
}

size_t CCanvasView::GetSelectedShapeNum() const
{
	if (m_frame->IsActive())
	{
		return m_targetShapePosition;
	}
	else
	{
		return UINT_MAX;
	}
}

void CCanvasView::AddShape(std::shared_ptr<CShapePresenter> const & shape, size_t pos)
{
	if (shape != nullptr)
	{
		if (pos >= m_shapes.size())
		{
			m_shapes.push_back(CreateShape(shape));
		}
		else
		{
			m_shapes.insert(m_shapes.begin() + pos, CreateShape(shape));
		}
	}
}

void CCanvasView::DeleteShape(size_t pos)
{
	if (m_shapes.size() > pos)
	{
		m_shapes.erase(m_shapes.begin() + pos);
	}
	if (pos == m_targetShapePosition)
	{
		m_frame->ResetTargget();
	}
}

void CCanvasView::MoveShapeLayer(size_t position, bool isToUp)
{
	if(isToUp)
	{
		MoveShapeUp(position);
		
	}
	else
	{
		MoveShapeDown(position);
	}
}

void CCanvasView::MoveShapeUp(size_t position)
{
	if (position < m_shapes.size() - 1)
	{
		auto tempShape = m_shapes[position + 1];
		m_shapes[position + 1] = m_shapes[position];
		m_shapes[position] = tempShape;
		if (m_targetShapePosition == position)
		{
			++m_targetShapePosition;
		}
	}
}

void CCanvasView::MoveShapeDown(size_t position)
{
	if (position > 0)
	{
		auto tempShape = m_shapes[position - 1];
		m_shapes[position - 1] = m_shapes[position];
		m_shapes[position] = tempShape;
		if (m_targetShapePosition == position)
		{
			--m_targetShapePosition;
		}
	}
}


void CCanvasView::Clear()
{
	m_frame->ResetTargget();
	m_shapes.clear();
}

void CCanvasView::Draw(sf::RenderTarget * window, CTextureCache * cache)
{
	CSolidLayer::Draw(window, cache);
	for (auto &shape : m_shapes)
	{
		shape->Draw(window, cache);
	}
	m_frame->DrawFrame(window);
}

std::shared_ptr<CShape> CCanvasView::CreateShape(std::shared_ptr<CShapePresenter> const& data)
{
	std::shared_ptr<CShape> shape;
	data->SetShapeView(shape);
	shape->SetAllowableArea(GetBoundingRect());
	shape->SetPresenter(data);
	return shape;
}

void CCanvasView::ShapeChangeRectEvent(std::shared_ptr<CShape> const & shape, sf::Event const& event)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		m_oldSelectShapeRect = shape->GetBoundingRect();
		break;
	case sf::Event::MouseButtonReleased:
		if (!(shape->GetPosition() == m_oldSelectShapeRect.position))
		{
			shape->OnChangeRect();
		}
		break;
	default:
		break;
	}
}

