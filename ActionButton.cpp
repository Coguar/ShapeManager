#include "stdafx.h"
#include "ActionButton.h"


CActionButton::CActionButton(SColor const& color)
	: m_defaultColor(color)
{
	SetColor(color);
	m_activateColor = m_defaultColor;
}


CActionButton::~CActionButton()
{
}

void CActionButton::SetAction(signal::Signal<void()>::slot_type const & action)
{
	m_connection = m_onClickAction.connect(action);
}

bool CActionButton::OnMousePressed(sf::Event::MouseButtonEvent const & event)
{
	if (GetBoundingRect().IsPointInRect({ double(event.x), double(event.y) }))
	{
		SetColor(m_activateColor);
		m_wasClicked = true;	
		return true;
	}
	return false;
}

bool CActionButton::OnMouseReleased(sf::Event::MouseButtonEvent const & event)
{
	SetColor(m_defaultColor);
	if (GetBoundingRect().IsPointInRect({ double(event.x), double(event.y) }) && m_wasClicked)
	{
		m_wasClicked = false;
		m_onClickAction();
		return true;
	}
	m_wasClicked = false;
	return false;
}

void CActionButton::SetActiveColor(SColor const & color)
{
	m_activateColor = color;
}

