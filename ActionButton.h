#pragma once
#include "ButtonInterface.h"
#include "Layer.h"

class CActionButton 
	: public CLayer
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

