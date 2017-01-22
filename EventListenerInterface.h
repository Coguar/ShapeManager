#pragma once
#include <SFML\Window.hpp>
#include "Reseiver.h"
struct IEventListener
{
	virtual bool OnEvent(sf::Event const& event) = 0;
	virtual bool OnMousePressed(sf::Event::MouseButtonEvent const& event) = 0;
	virtual bool OnMouseReleased(sf::Event::MouseButtonEvent const& event) = 0;
	virtual bool OnMouseMoved(sf::Event::MouseMoveEvent const& event) = 0;
	virtual void SetReseiver(std::shared_ptr<IReseiver> const& reseiver) = 0;
	virtual std::shared_ptr<IReseiver> const& GetReseiver() const = 0;
	virtual ~IEventListener() = default;
};