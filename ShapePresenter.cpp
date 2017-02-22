#include "stdafx.h"
#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include "PictureView.h"
#include "Picture.h"
#include "History.h"
#include "ChangeShapeRectCommand.h"
#include "ShapePresenter.h"
#include <vld.h>


CShapePresenter::CShapePresenter(std::shared_ptr<SModelShape> const& model, IHistory * history)
	: m_model(model)
	, m_history(history)
{
}

CShapePresenter::~CShapePresenter()
{
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
		m_connections.push_back(m_shape->DoOnChangeRect(boost::bind(&CShapePresenter::AddCommand, this)));
		m_connections.push_back(m_model->DoOnRectChanged(boost::bind(&CShape::SetBoundingRect, m_shape, _1)));
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
			shape = std::make_shared<ÑSquare>();
			break;
		case ShapeType::Picture:
			shape = std::make_shared<CPictureView>();
			shape->SetTexturePath(dynamic_cast<CPicture*>(m_model.get())->GetTexturePath());
			shape->SetColor(color::WHITE);
			break;
		default:
			shape = std::make_shared<CCircle>();
			break;
		}
		if (m_model->GetType() != ShapeType::Picture)
		{
			shape->SetColor(color::SHAPE_COLOR);
		}
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

