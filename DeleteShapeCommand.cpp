#include "stdafx.h"
#include "DeleteShapeCommand.h"

CDeleteShapeCommand::CDeleteShapeCommand(std::shared_ptr<CShape> const & shape, size_t position)
	: m_shape(shape)
	, m_shapePosition(position)
{
}

CDeleteShapeCommand::~CDeleteShapeCommand()
{
}

void CDeleteShapeCommand::Execute()
{
	if (m_canvas != nullptr)
	{
		m_canvas->DeleteShapeByPosition(m_shapePosition);
		m_canvas->GetFSelectFrame()->ResetTargget();
	}
}

void CDeleteShapeCommand::Unexecute()
{
	if (m_canvas != nullptr)
	{
		m_canvas->AddShape(m_shape, m_shapePosition);
	}
}
