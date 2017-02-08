#include "stdafx.h"
#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include "ShapeModel.h"
#include "History.h"
#include "ChangeShapeRectCommand.h"
#include "ShapePresenter.h"


CShapePresenter::CShapePresenter(std::shared_ptr<SModelShape> const& model)
	: m_model(model)
{
}

CShapePresenter::~CShapePresenter()
{
}

void CShapePresenter::SetHistory(CHistory * history)
{
	m_history = history;
}

void CShapePresenter::SetShapeView(std::shared_ptr<CShape> & shape)
{
	InitView(shape);
	m_shape = shape.get();
	SetConnects();
}

void CShapePresenter::SetConnects()
{
	if (m_shape && m_model)
	{
		m_connection = m_shape->DoOnChangeRect(boost::bind(&CShapePresenter::AddCommand, this));
		m_model->DoOnRectChanged(boost::bind(&CShape::SetBoundingRect, m_shape, _1));
	}
}

void CShapePresenter::InitView(std::shared_ptr<CShape> & shape)
{
	if (m_model)
	{
		switch (m_model->GetType())
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
		shape->SetPosition(m_model->GetPosition());
		shape->SetSize(m_model->GetSize());
	}
}

void CShapePresenter::AddCommand()
{
	if (m_history && m_shape && m_model)
	{
		m_history->PushCommand(std::make_shared<CChangeShapeRectCommand>(m_shape->GetBoundingRect(), CBoundingRect(m_model->GetPosition(), m_model->GetSize()), m_model));
	}
}
