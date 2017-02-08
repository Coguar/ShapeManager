#include "stdafx.h"
#include "SelectFrame.h"

CSelectFrame::CSelectFrame()
{
	for (size_t i = 0; i < 4; ++i)
	{
		auto point = std::make_shared<CDragPoint>();
		point->SetColor(color::DRAG_POINT_COLOR);
		point->SetSize(DRAG_POINT_SIZE);
		m_dragPoints.push_back(point);
	}
	m_dragPoints[0]->SetConnectedPoint(m_dragPoints[1], m_dragPoints[3]);
	m_dragPoints[1]->SetConnectedPoint(m_dragPoints[0], m_dragPoints[2]);
	m_dragPoints[2]->SetConnectedPoint(m_dragPoints[3], m_dragPoints[1]);
	m_dragPoints[3]->SetConnectedPoint(m_dragPoints[2], m_dragPoints[0]);

}

CSelectFrame::~CSelectFrame()
{
}

bool CSelectFrame::OnEvent(sf::Event const & event)
{
	for (auto &point : m_dragPoints)
	{
		if (point->OnEvent(event) && m_targetShape != nullptr)
		{
			m_targetShape->SetSize(m_dragPoints[0]->GetDistantionFromConnections());
			auto pointPos = m_dragPoints[0]->GetPosition();
			auto pointSize = m_dragPoints[0]->GetSize();
			m_targetShape->SetPosition({ pointPos.x + pointSize.x / 2.0,  pointPos.y + pointSize.y / 2.0 });
			OnResizeFrame(event);
			return true;
		}
	}
	return false;
}

void CSelectFrame::SetTarget(std::shared_ptr<CShape> const & shape, size_t num)
{
	m_connection.disconnect();
	m_targetShape = shape;
	m_connection = m_targetShape->DoOnProgramChangeRect(boost::bind(&CSelectFrame::SetPoints, this));
	SetPoints();
}

std::shared_ptr<CShape> const & CSelectFrame::GetTarget() const
{
	return m_targetShape;
}

std::vector<std::shared_ptr<CDragPoint>> CSelectFrame::GetDragPoints() const
{
	return m_dragPoints;
}

void CSelectFrame::ResetTargget()
{
	m_targetShape.reset();
}

bool CSelectFrame::IsActive() const
{
	return m_targetShape != nullptr;
}

CBoundingRect const & CSelectFrame::GetTargetRect() const
{
	return m_targetShape->GetBoundingRect();
}

void CSelectFrame::DrawFrame(sf::RenderTarget * window)
{
	if (window != nullptr && m_targetShape != nullptr)
	{
		auto size = m_targetShape->GetSize();
		auto position = m_targetShape->GetPosition();
		sf::RectangleShape frame({ float(size.x), float(size.y) });
		frame.setFillColor(sf::Color(0, 0, 0, 0));
		frame.setOutlineThickness(2.f);
		frame.setOutlineColor(sf::Color::Green);
		frame.setPosition({ float(position.x), float(position.y) });
		window->draw(frame);

		for (auto &point : m_dragPoints)
		{
			point->Draw(window, nullptr);
		}
	}
}

void CSelectFrame::DoOnResize(std::function<void()> const& action)
{
	m_onResizeShape.connect(action);
}

void CSelectFrame::SetPoints()
{
	if (m_targetShape != nullptr)
	{
		auto rect = m_targetShape->GetBoundingRect();
		auto pointRadius = m_dragPoints[0]->GetBoundingRect().size.x / 2.0;
		m_dragPoints[0]->SetPosition({ rect.position.x - pointRadius, rect.position.y - pointRadius });
		m_dragPoints[1]->SetPosition({ rect.position.x + rect.size.x - pointRadius, rect.position.y - pointRadius });
		m_dragPoints[3]->SetPosition({ rect.position.x - pointRadius, rect.position.y + rect.size.y - pointRadius });
		m_dragPoints[2]->SetPosition({ rect.position.x + rect.size.x - pointRadius, rect.position.y + rect.size.y - pointRadius });

		for (auto &point : m_dragPoints)
		{
			point->SetAllowableArea(m_targetShape->GetAllowableArea());
		}
	}
}

void CSelectFrame::OnResizeFrame(sf::Event const & event)
{
	if (m_targetShape != nullptr)
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			m_oldFrameSize = m_targetShape->GetBoundingRect();
			break;
		case sf::Event::MouseButtonReleased:
			break;
		default:
			break;
		}
	}
}