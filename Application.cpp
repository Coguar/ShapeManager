#include "stdafx.h"
#include "MainView.h"
#include "ApplicationModel.h"
#include "Controller.h"
#include "Application.h"


CApplication::CApplication()
{
	m_controller = std::make_shared<CController>();
	m_appModel = std::make_shared<CApplicationModel>();
	m_view = std::make_shared<CMainView>();
	m_controller->SetModelManipulator(m_appModel.get());
	m_controller->SetSignalsConnector(m_appModel.get());
	m_controller->SetView(m_view);
}


CApplication::~CApplication()
{
}

void CApplication::Start()
{
	m_controller->Start();
}
