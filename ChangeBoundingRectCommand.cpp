#include "stdafx.h"
#include "ChangeBoundingRectCommand.h"

CChangeBoundingRectCommand::CChangeBoundingRectCommand(size_t position, CBoundingRect const& newRect, CBoundingRect const& oldRect, CDomainModel* model)
	: CMyCommand(model)
	, m_oldRect(oldRect)
	, m_newRect(newRect)
	, m_shapePosition(position)
{
}

CChangeBoundingRectCommand::~CChangeBoundingRectCommand()
{
}

void CChangeBoundingRectCommand::Execute()
{
	if (m_model != nullptr)
	{
		m_model->ChangeShapeSettings(m_shapePosition, m_newRect.position, m_newRect.size);
	}
}

void CChangeBoundingRectCommand::Unexecute()
{
	if (m_model != nullptr)
	{
		m_model->ChangeShapeSettings(m_shapePosition, m_oldRect.position, m_oldRect.size);
	}
}
