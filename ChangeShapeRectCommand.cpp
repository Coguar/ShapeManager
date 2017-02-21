#include "stdafx.h"
#include "ShapeModel.h"
#include "ChangeShapeRectCommand.h"

CChangeShapeRectCommand::CChangeShapeRectCommand(CBoundingRect const & newRect, CBoundingRect const & oldRect, std::shared_ptr<SModelShape> const & shapeModel)
	: m_oldRect(oldRect)
	, m_newRect(newRect)
	, m_model(shapeModel)
{
}

CChangeShapeRectCommand::~CChangeShapeRectCommand()
{
}

void CChangeShapeRectCommand::Execute()
{
	if (!m_isDone)
	{
		m_model->SetRect(m_newRect.position, m_newRect.size);
		SetDoneState(true);
	}
}

void CChangeShapeRectCommand::Unexecute()
{
	if (m_isDone)
	{
		m_model->SetRect(m_oldRect.position, m_oldRect.size);
		SetDoneState(false);
	}
}

void CChangeShapeRectCommand::Destroy()
{
}
