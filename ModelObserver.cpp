#include "stdafx.h"
#include "ModelObserver.h"
#include "MainView.h"

CModelObserver::CModelObserver()
{
}


CModelObserver::~CModelObserver()
{
}

void CModelObserver::Update(DataType const & data)
{
	if (m_view != nullptr)
	{
		for (auto &event : data)
		{
			EditEvent(event);
		}
	}
}

void CModelObserver::SetView(CMainView * view)
{
	m_view = view;
}

void CModelObserver::EditEvent(DomEvent const & event)
{
	m_view->SetDocDataState(false);
	switch (event.m_type)
	{
	case DomEventType::Add:
		m_view->GetCanvas()->AddShape(event.m_element, event.m_pos);
		break;
	case DomEventType::Del:
		m_view->GetCanvas()->DeleteShape(event.m_pos);
		break;
	case DomEventType::Change:
		m_view->GetCanvas()->UpdateShape(event.m_pos, CBoundingRect(event.m_element->m_position, event.m_element->m_size));
		break;
	case DomEventType::Clear:
		m_view->GetCanvas()->Clear();
		break;
	case DomEventType::Saved:
		m_view->SetDocDataState(true);
		break;
	default:
		break;
	}
}
