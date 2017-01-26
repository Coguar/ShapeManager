#include "stdafx.h"
#include "Controller.h"

CController::CController(sf::RenderWindow * target)
	: m_target(target)
{
	m_model = std::make_unique<CAppModel>();
	m_view = std::make_unique<CSceneView>(m_target);
}

CController::~CController()
{
}

void CController::Start()
{
	if (m_target == nullptr)
	{
		return;
	}
	while (m_target->isOpen())
	{
		sf::Event event;
		while (m_target->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_target->close();
				break;
			case sf::Event::KeyPressed:
				OnKeyPressed(event.key);
				break;
			default:
				m_model->GetRoot()->DispatchEvent(event);
				break;
			}
		}
		m_model->GetRoot()->Update();
		Draw();
	}
}

void CController::Draw()
{
	m_target->clear();
	m_view->Draw(m_model->GetRoot().get());
	m_view->DrawShapes(m_model->GetCanvas()->GetShapes());
	m_view->DrawSelectFrame(m_model->GetCanvas()->GetFSelectFrame());
	m_target->display();
}

void CController::OnKeyPressed(sf::Event::KeyEvent const & event)
{
	switch (event.code)
	{
	case sf::Keyboard::Delete:
		m_model->DeleteSelectedShape();
		break;
	default:
		break;
	}
}
