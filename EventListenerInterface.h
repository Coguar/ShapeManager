#pragma once
#include <SFML\Window.hpp>

struct IEventListener
{
	virtual bool OnEvent(sf::Event const& event) = 0;
	virtual ~IEventListener() = default;
};