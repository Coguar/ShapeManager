#include "stdafx.h"
#include "ViewObserver.h"
#include "ApplicationModel.h"
#include "ViewEvent.h"

CViewObserver::CViewObserver()
{
}


CViewObserver::~CViewObserver()
{
}

void CViewObserver::Update(SEvent const & data)
{
	EditEvent(data);
}

void CViewObserver::SetModel(CApplicationModel * appModel)
{
	m_appModel = appModel;
}

void CViewObserver::EditEvent(SEvent const & data)
{
	if (m_appModel == nullptr)
		return;

	switch (data.m_type)
	{
	case EventType::AddCircle:
		AddShapeEvent(ShapeType::Circle, data.m_newRect.position);
		break;
	case EventType::AddRectangle:
		AddShapeEvent(ShapeType::Rectangle, data.m_newRect.position);
		break;
	case EventType::AddTriangle:
		AddShapeEvent(ShapeType::Triangle, data.m_newRect.position);
		break;
	case EventType::DeleteShape:
		DeleteShapeEvent(data.m_shapeNumber);
		break;
	case EventType::ChangeShapeRect:
		ChangeShapeRectEvent(data.m_shapeNumber, data.m_newRect);
		break;
	case EventType::Redo:
		RedoEvent();
		break;
	case EventType::Undo:
		UndoEvent();
		break;
	case EventType::Save:
		SaveEvent(data.m_filePath);
		break;
	case EventType::Open:
		OpenEvent(data.m_filePath);
		break;
	default:
		break;
	}
}

void CViewObserver::AddShapeEvent(ShapeType type, Vec2 const& position)
{
	if (m_appModel != nullptr)
	{
		m_appModel->AddShape(type, position);
	}
}

void CViewObserver::DeleteShapeEvent(size_t number)
{
	if (m_appModel != nullptr)
	{
		m_appModel->DeleteShape(number);
	}
}

void CViewObserver::ChangeShapeRectEvent(size_t number, CBoundingRect const & newRect)
{
	if (m_appModel != nullptr)
	{
		std::cout << "PPPP" << std::endl;
		m_appModel->ChangeShapeRect(number, newRect.position, newRect.size);
	}
}

void CViewObserver::RedoEvent()
{
	if (m_appModel != nullptr)
	{
		m_appModel->RedoCommand();
	}
}

void CViewObserver::UndoEvent()
{
	if (m_appModel != nullptr)
	{
		m_appModel->UndoCommand();
	}
}

void CViewObserver::SaveEvent(std::string const & path)
{
	if (m_appModel != nullptr)
	{
		m_appModel->Save(path);
	}
}

void CViewObserver::OpenEvent(std::string const & path)
{
	if (m_appModel != nullptr)
	{
		m_appModel->Open(path);
	}
}
