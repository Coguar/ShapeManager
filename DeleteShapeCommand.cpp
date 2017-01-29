#include "stdafx.h"
#include "DeleteShapeCommand.h"

CDeleteShapeCommand::CDeleteShapeCommand(size_t position, CDomainModel* model)
	: CMyCommand(model)
	, m_shapePosition(position)
{
}

CDeleteShapeCommand::~CDeleteShapeCommand()
{
}

void CDeleteShapeCommand::Execute()
{
	if (m_model != nullptr)
	{
		m_shape = m_model->DeleteShapeByPosition(m_shapePosition);
	}
}

void CDeleteShapeCommand::Unexecute()
{
	if (m_model != nullptr)
	{
		m_model->AddShape(m_shape, m_shapePosition);
	}
}
