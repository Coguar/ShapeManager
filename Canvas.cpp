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

std::shared_ptr<CAbstractShape> CCanvas::CreateShape(shape::Type type)
{
	std::shared_ptr<CAbstractShape> shape;
	switch (type)
	{
	case shape::Type::Circle:
		shape = std::make_shared<CCircle>();
		break;
	case shape::Type::Triangle:
		shape = std::make_shared<CTriangle>();
		break;
	case shape::Type::Rectangle:
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

std::vector<std::shared_ptr<CAbstractShape>> const& CCanvas::GetShapes() const
{
	return m_shapes;
}

bool CCanvas::OnEvent(sf::Event const & event)
{
	for (auto &shape : m_shapes)
	{
		shape->OnEvent(event);
	}
	return true;
}

void CCanvas::SetShape(std::shared_ptr<CAbstractShape>& shape)
{
	shape->SetColor(SColor(255, 0, 255, 255));
	SCoords position(GetPosition().x + GetSize().x / 2.0, GetPosition().y + GetSize().x / 2.0);
	shape->SetSize({ 40, 40 });
}

