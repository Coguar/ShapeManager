#include "stdafx.h"
#include "Picture.h"
#include "FileManager.h"
#include "DeleteShapeCommand.h"

CDeleteShapeCommand::CDeleteShapeCommand(size_t position, CCanvas* model)
	: CCanvasCommand(model)
	, m_shapePosition(position)
{
}

CDeleteShapeCommand::~CDeleteShapeCommand()
{
}

void CDeleteShapeCommand::Execute()
{
	if (!m_isDone && m_model != nullptr)
	{
		m_shape = m_model->DeleteShapeByPosition(m_shapePosition);
		SetDoneState(true);
	}
}

void CDeleteShapeCommand::Unexecute()
{
	if (m_isDone && m_model != nullptr)
	{
		m_model->AddShape(m_shape, m_shapePosition);
		SetDoneState(false);
	}
}

void CDeleteShapeCommand::Destroy()
{
	if (m_shape->GetType() == ShapeType::Picture)
	{
		CFileManager::RemoveFile(dynamic_cast<CPicture*>(m_shape.get())->GetTexturePath());
	}
}