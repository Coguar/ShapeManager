#include "stdafx.h"
#include "ChangeLayerCommand.h"

CChangeLayerCommand::CChangeLayerCommand(size_t position, bool isToUp, CCanvas * model)
	: CCanvasCommand(model)
	, m_isToUp(isToUp)
	, m_position(position)
{
}

CChangeLayerCommand::~CChangeLayerCommand()
{
}

void CChangeLayerCommand::Execute()
{
	if (m_isToUp)
	{
		m_model->MoveShapeUp(m_position);
	}
	else
	{
		m_model->MoveShapeDown(m_position);
	}
}

void CChangeLayerCommand::Unexecute()
{
	if (m_isToUp)
	{
		m_model->MoveShapeUp(m_position);
	}
	else
	{
		m_model->MoveShapeDown(m_position);
	}
}
