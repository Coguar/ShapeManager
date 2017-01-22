#include "stdafx.h"
#include "Circle.h"
#include "Triangle.h"
#include "Square.h"
#include "Reseiver.h"
#include "Canvas.h"


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
	shape->SetReseiver(GetReseiver());
	GetReseiver()->AddShape(shape);
	return shape;
}

void CCanvas::AddShape(std::shared_ptr<CShape> const & shape)
{
	m_shapes.push_back(shape);
}

void CCanvas::AddShape(std::shared_ptr<CShape> const& shape, size_t position)
{
	m_shapes.insert(m_shapes.begin() + position, shape);
}

void CCanvas::DeleteLastShape()
{
	m_shapes.pop_back();
}

void CCanvas::DeleteShapeByPosition(size_t position)
{
	m_shapes.erase(m_shapes.begin() + position);
}

bool CCanvas::DeleteSelectedShape()
{
	if (m_frame->GetTarget() != nullptr)
	{
		GetReseiver()->DeleteShape(m_frame->GetTarget(), m_targetShapePosition);
		m_frame->ResetTargget();
		return true;
	}
	return false;
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
			m_frame->SetTarget(m_shapes[i]);
			ShapeChangeRectEvent(m_shapes[i], event);
			m_targetShapePosition = i;
			return true;
		}
	}
	return false;
}

bool CCanvas::OnMousePressed(sf::Event::MouseButtonEvent const & event)
{
	m_frame->ResetTargget();
	return false;
}

std::shared_ptr<CSelectFrame> const & CCanvas::GetFSelectFrame() const
{
	return m_frame;
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
			GetReseiver()->ChangeRect(shape, m_oldSelectShapeRect);
		break;
	default:
		break;
	}
}

void CCanvas::SetShape(std::shared_ptr<CShape> const& shape)
{
	shape->SetColor(color::SHAPE_COLOR);
	Vec2 position(GetPosition().x + GetSize().x / 2.0, GetPosition().y + GetSize().y / 2.0);
	shape->SetPosition(position);
	shape->SetSize(INITIALIZATION_SHAPE_SIZE);
	shape->SetAllowableArea(GetBoundingRect());
}

