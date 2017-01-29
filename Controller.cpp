#include "stdafx.h"
#include "Controller.h"


CController::CController()
{
	m_appModel = std::make_unique<CApplicationModel>();
	m_view = std::make_unique<CMainView>();

	m_viewObserver = std::make_unique<CViewObserver>();
	m_modelObserver = std::make_unique<CModelObserver>();

	m_viewObserver->SetModel(m_appModel.get());
	m_modelObserver->SetView(m_view.get());

	m_appModel->RegisterObserver(*m_modelObserver.get());
	m_view->RegisterObserver(*m_viewObserver.get());
}


CController::~CController()
{
}

void CController::Start()
{
	m_view->StartShow();
}
