#include "stdafx.h"
#include "Canvas.h"
#include "Circle.h"
#include "Triangle.h"
#include "Square.h"

CCanvas::CCanvas()
{
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
	for (auto &shape : m_shapes)
	{
		if (shape->OnEvent(event))
		{
			break;
		}
	}
	return true;
}

void CCanvas::SetShape(std::shared_ptr<CShape> const& shape)
{
	shape->SetColor(SColor(255, 0, 255, 255));
	Vec2 position(GetPosition().x + GetSize().x / 2.0, GetPosition().y + GetSize().y / 2.0);
	shape->SetPosition(position);
	shape->SetSize({ 40, 40 });
}

