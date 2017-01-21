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
			m_model->GetRoot()->DispatchEvent(event);
			if (event.type == sf::Event::Closed)
				m_target->close();
		}
		m_view->Draw(m_model->GetRoot().get());
		m_view->DrawShapes(m_model->GetCanvas()->GetShapes());
		m_view->DrawSelectFrame(m_model->GetCanvas()->GetFSelectFrame());
		m_target->display();
		m_target->clear();
	}
}
