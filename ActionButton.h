#pragma once
#include "ButtonInterface.h"
#include "Layer.h"

class CActionButton : public CLayer, public IButton
{
public:
	CActionButton();
	~CActionButton();
	void SetAction(signal::Signal<void()>::slot_type const& action) override;
	void DoClickAction() override;
private:
	signal::Connection m_connection;
	signal::Signal<void()> m_onClickAction;
};

