#include "stdafx.h"
#include "Canvas.h"
#include "Circle.h"
#include "Triangle.h"
#include "Square.h"

CCanvas::CCanvas()
{
	m_frame = std::make_shared<CSelectFrame>();
}


CCanvas::~CCanvas()
{
}

std::shared_ptr<CShape> CCanvas::CreateShape(ShapeType type)
{
	std::shared_ptr<CShape> shape;
	switch (type)
	{
	case ShapeType::Circle:
		shape = std::make_shared<CCircle>();
		break;
	case ShapeType::Triangle:
		shape = std::make_shared<CTriangle>();
		break;
	case ShapeType::Rectangle:
		shape = std::make_shared<ÑSquare>();
		break;
	default:
		shape = std::make_shared<CCircle>();
		break;
	}
	SetShape(shape);
	m_shapes.push_back(shape);
	return shape;
}

std::vector<std::shared_ptr<CShape>> const& CCanvas::GetShapes() const
{
	return m_shapes;
}

bool CCanvas::OnEvent(sf::Event const & event)
{
	if (m_frame->OnEvent(event))
	{
		return true;
	}
	CParentLayer::OnEvent(event);
	for (int i = m_shapes.size() - 1; i >= 0; --i)
	{
		if (m_shapes[i]->OnEvent(event))
		{
			m_shapes.push_back(m_shapes[i]);			
			m_shapes.erase(m_shapes.begin() + i);
			m_frame->SetTarget(m_shapes.back());
			return true;
		}
	}
	return false;
}

bool CCanvas::OnMousePressed(sf::Event::MouseButtonEvent const & event)
{
	m_frame->ResetTargget();
	return true;
}

std::shared_ptr<CSelectFrame> const & CCanvas::GetFSelectFrame() const
{
	return m_frame;
}

void CCanvas::SetShape(std::shared_ptr<CShape> const& shape)
{
	shape->SetColor(color::SHAPE_COLOR);
	Vec2 position(GetPosition().x + GetSize().x / 2.0, GetPosition().y + GetSize().y / 2.0);
	shape->SetPosition(position);
	shape->SetSize(INITIALIZATION_SHAPE_SIZE);
	shape->SetAllowableArea(GetBoundingRect());
}

