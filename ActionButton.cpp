#include "stdafx.h"
#include "ActionButton.h"


CActionButton::CActionButton()
{
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
	m_onClickAction();
	return true;
}

