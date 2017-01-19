#pragma once
#include <SFML\Window.hpp>

struct IEventListener
{
	virtual bool OnEvent(sf::Event const& event) = 0;
	virtual bool OnMousePressed(sf::Event::MouseButtonEvent const& event) = 0;
	virtual bool OnMouseReleased(sf::Event::MouseButtonEvent const& event) = 0;
	virtual bool OnMouseMoved(sf::Event::MouseMoveEvent const& event) = 0;
	virtual ~IEventListener() = default;
};