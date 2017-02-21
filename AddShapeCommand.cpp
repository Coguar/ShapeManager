#include "stdafx.h"
#include "AddShapeCommand.h"
#include "FileManager.h"
#include "Picture.h"

CAddShapeCommand::CAddShapeCommand(std::shared_ptr<SModelShape> const& shape, CCanvas* model)
	: CCanvasCommand(model)
	, m_shape(shape)
{
}


CAddShapeCommand::~CAddShapeCommand()
{
}

void CAddShapeCommand::Execute()
{
	if (!m_isDone && m_model != nullptr && m_shape != nullptr)
	{
		m_model->AddShape(m_shape);
		SetDoneState(true);
	}
}

void CAddShapeCommand::Unexecute()
{
	if (m_isDone && m_model != nullptr && m_shape != nullptr)
	{
		m_model->DeleteLastShape();
		SetDoneState(false);
	}
}

void CAddShapeCommand::Destroy()
{
	if (m_shape->GetType() == ShapeType::Picture)
	{
		CFileManager::RemoveFile(dynamic_cast<CPicture*>(m_shape.get())->GetTexturePath());
	}
}
