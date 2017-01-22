#include "stdafx.h"
#include "ChangeBoundingRectCommand.h"

CChangeBoundingRectCommand::CChangeBoundingRectCommand(std::shared_ptr<CShape> const & shape, CBoundingRect const & oldRect)
	: m_shape(shape)
	, m_oldRect(oldRect)
	, m_newRect(shape->GetBoundingRect())
{
}

CChangeBoundingRectCommand::~CChangeBoundingRectCommand()
{
}

void CChangeBoundingRectCommand::Execute()
{
	m_shape->SetBoundingRect(m_newRect);
}

void CChangeBoundingRectCommand::Unexecute()
{
	m_shape->SetBoundingRect(m_oldRect);
}
