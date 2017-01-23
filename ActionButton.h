#pragma once
#include "ParentLayer.h"

class CActionButton 
	: public CParentLayer
{
public:
	CActionButton(SColor const& color);
	~CActionButton();
	void SetAction(signal::Signal<void()>::slot_type const& action);
	bool OnMousePressed(sf::Event::MouseButtonEvent const& event) override;
	bool OnMouseReleased(sf::Event::MouseButtonEvent const& event) override;

	void SetActiveColor(SColor const& color);
private:
	boost::signals2::scoped_connection m_connection;
	signal::Signal<void()> m_onClickAction;

	SColor m_defaultColor;
	SColor m_activateColor;
	bool m_wasClicked = false;
};

