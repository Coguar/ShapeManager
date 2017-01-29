#pragma once
#include "MainView.h"
#include "ModelObserver.h"
#include "ViewObserver.h"

class CController
{
public:
	CController();
	~CController();
	void Start();
private:
	std::unique_ptr<CApplicationModel> m_appModel;
	std::unique_ptr<CMainView> m_view;

	std::unique_ptr<CViewObserver> m_viewObserver;
	std::unique_ptr<CModelObserver> m_modelObserver;
};

