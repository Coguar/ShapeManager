#pragma once
#include "ApplicationModel.h"

class CMainView;

class CModelObserver :
	public IObserver<DataType>
{
public:
	CModelObserver();
	~CModelObserver();
	void Update(DataType const& data) override;
	void SetView(CMainView * view);

private:
	void EditEvent(DomEvent const& event);

	CMainView * m_view;
};

