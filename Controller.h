#pragma once
#include "MainView.h"
#include "ApplicationModel.h"

class CController
{
public:
	CController();
	~CController();
	void Start();
private:
	void ConnectSignalsFromView();
	void ConnectSignalsFromModel();

	std::shared_ptr<CApplicationModel> m_appModel;
	std::shared_ptr<CMainView> m_view;
};

