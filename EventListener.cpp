#include "stdafx.h"
#include "EventListener.h"

bool CEventListener::OnEvent(sf::Event const & event)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		return OnMousePressed(event.mouseButton);
	case sf::Event::MouseButtonReleased:
		return OnMouseReleased(event.mouseButton);
	case sf::Event::MouseMoved:
		return OnMouseMoved(event.mouseMove);
	default:
		return false;
	}
}

bool CEventListener::OnMousePressed(sf::Event::MouseButtonEvent const & event)
{
	return false;
}

bool CEventListener::OnMouseReleased(sf::Event::MouseButtonEvent const & event)
{
	return false;
}

bool CEventListener::OnMouseMoved(sf::Event::MouseMoveEvent const & event)
{
	return false;
}