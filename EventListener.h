#pragma once
#include "EventListenerInterface.h"
class CEventListener :
	public IEventListener
{
public:
	CEventListener() = default;
	~CEventListener() = default;

	bool OnEvent(sf::Event const& event) override;
	bool OnMousePressed(sf::Event::MouseButtonEvent const& event) override;
	bool OnMouseReleased(sf::Event::MouseButtonEvent const& event) override;
	bool OnMouseMoved(sf::Event::MouseMoveEvent const& event) override;
};

