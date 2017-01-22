#include "stdafx.h"
#include "AddShapeCommand.h"


CAddShapeCommand::CAddShapeCommand(std::shared_ptr<CShape> const& shape)
	: m_shape(shape)
{
}


CAddShapeCommand::~CAddShapeCommand()
{
}

void CAddShapeCommand::Execute()
{
	if (m_canvas != nullptr && m_shape != nullptr)
	{
		m_canvas->AddShape(m_shape);
	}
}

void CAddShapeCommand::Unexecute()
{
	if (m_canvas != nullptr && m_shape != nullptr)
	{
		m_canvas->DeleteLastShape();
	}
}
