#pragma once
#include "ButtonInterface.h"
#include "ParentLayer.h"

class CActionButton 
	: public CParentLayer
{
public:
	CActionButton();
	~CActionButton();
	void SetAction(signal::Signal<void()>::slot_type const& action);
	bool OnMousePressed(sf::Event::MouseButtonEvent const& event) override;
private:
	boost::signals2::scoped_connection m_connection;
	signal::Signal<void()> m_onClickAction;
};

