#pragma once
#include "EventListenerInterface.h"

class CEventListener :
	public IEventListener
{
public:
	CEventListener() = default;
	virtual ~CEventListener() = default;

	bool OnEvent(sf::Event const& event) override;

protected:
	virtual bool OnMousePressed(sf::Event::MouseButtonEvent const& event);
	virtual bool OnMouseReleased(sf::Event::MouseButtonEvent const& event);
	virtual bool OnMouseMoved(sf::Event::MouseMoveEvent const& event);
};

