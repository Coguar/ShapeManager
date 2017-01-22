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
				OnKeyPressed(event);
				break;
			default:
				m_model->GetRoot()->DispatchEvent(event);
				break;
			}
		}
		Draw();
	}
}

void CController::Draw()
{
	m_view->Draw(m_model->GetRoot().get());
	m_view->DrawShapes(m_model->GetCanvas()->GetShapes());
	m_view->DrawSelectFrame(m_model->GetCanvas()->GetFSelectFrame());
	m_target->display();
	m_target->clear();
}

void CController::OnKeyPressed(sf::Event const & event)
{
	switch (event.key.code)
	{
	case sf::Keyboard::Delete:
		m_model->DeleteSelectedShape();
		break;
	default:
		break;
	}
}
