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
	m_model->SetRect(m_newRect.position, m_newRect.size);
}

void CChangeShapeRectCommand::Unexecute()
{
	m_model->SetRect(m_oldRect.position, m_oldRect.size);
}

void CChangeShapeRectCommand::Destroy()
{
}
