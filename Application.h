#pragma once

class CApplicationModel;
class CMainView;
class CController;

class CApplication
{
public:
	CApplication();
	~CApplication();

	void Start(std::string const& filePath = std::string());

private:
	std::shared_ptr<CController> m_controller;
	std::shared_ptr<CApplicationModel> m_appModel;
	std::shared_ptr<CMainView> m_view;

};

