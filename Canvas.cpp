#include "stdafx.h"
#include "Circle.h"
#include "Triangle.h"
#include "Square.h"
#include "Reseiver.h"
#include "ShapeModel.h"
#include "Canvas.h"


CCanvas::CCanvas()
{
	m_frame = std::make_shared<CSelectFrame>();
	m_frame->DoOnResize(boost::bind(&CCanvas::ChangeShapeRect, this));
}


CCanvas::~CCanvas()
{
}

bool CCanvas::OnEvent(sf::Event const & event)
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

bool CCanvas::OnMousePressed(sf::Event::MouseButtonEvent const & event)
{
	if (GetBoundingRect().IsPointInRect({ double(event.x), double(event.y) }))
	{
		m_frame->ResetTargget();
		return true;
	}
	return false;
}

std::shared_ptr<CSelectFrame> const & CCanvas::GetFSelectFrame() const
{
	return m_frame;
}

size_t CCanvas::GetSelectedShapeNum() const
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

void CCanvas::AddShape(std::shared_ptr<SModelShape> const & shape, size_t pos)
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

void CCanvas::DeleteShape(size_t pos)
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

void CCanvas::SetNewShapesList(std::vector<std::shared_ptr<SModelShape>> const& shapes)
{
	if (shapes.size() < m_shapes.size())
	{
		m_frame->ResetTargget();
	}
	m_shapes.clear();
	for (auto &shape : shapes)
	{
		m_shapes.push_back(CreateShape(shape));
	}
}

void CCanvas::Clear()
{
	m_frame->ResetTargget();
	m_shapes.clear();
}

void CCanvas::Draw(sf::RenderTarget * window, CTextureCache * cache)
{
	CSolidLayer::Draw(window, cache);
	for (auto &shape : m_shapes)
	{
		shape->Draw(window, cache);
	}
	m_frame->DrawFrame(window);
}

void CCanvas::DoOnShapeRectChanged(std::function<void(size_t, const CBoundingRect&)> const & action)
{
	m_onShapesRectChange.connect(action);
}

std::shared_ptr<CShape> CCanvas::CreateShape(std::shared_ptr<SModelShape> const& data)
{
	std::shared_ptr<CShape> shape;
	switch (data->GetType())
	{
	case ShapeType::Circle:
		shape = std::make_shared<CCircle>();
		break;
	case ShapeType::Triangle:
		shape = std::make_shared<CTriangle>();
		break;
	case ShapeType::Rectangle:
		shape = std::make_shared<�Square>();
		break;
	default:
		shape = std::make_shared<CCircle>();
		break;
	}
	shape->SetColor(color::SHAPE_COLOR);
	shape->SetPosition(data->GetPosition());
	shape->SetSize(data->GetSize());
	shape->SetAllowableArea(GetBoundingRect());

	data->DoOnRectChanged(boost::bind(&CShape::SetBoundingRect, shape.get(), _1));
	return shape;
}

void CCanvas::ShapeChangeRectEvent(std::shared_ptr<CShape> const & shape, sf::Event const& event)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		m_oldSelectShapeRect = shape->GetBoundingRect();
		break;
	case sf::Event::MouseButtonReleased:
		if (!(shape->GetPosition() == m_oldSelectShapeRect.position))
		{
			ChangeShapeRect();
		}
		break;
	default:
		break;
	}
}

void CCanvas::ChangeShapeRect()
{
	m_onShapesRectChange(m_targetShapePosition, m_shapes[m_targetShapePosition]->GetBoundingRect());
}

