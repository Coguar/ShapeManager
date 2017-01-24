#include "stdafx.h"
#include "SelectFrame.h"

CSelectFrame::CSelectFrame()
{
	CDragPoint point;
	point.SetColor(color::DRAG_POINT_COLOR);
	point.SetSize(DRAG_POINT_SIZE);
	for (size_t i = 0; i < 4; ++i)
	{
		m_dragPoints.push_back(std::make_shared<CDragPoint>(point));
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
			SendCommandToReseiver(event);
			return true;
		}
	}
	return false;
}

void CSelectFrame::SetTarget(std::shared_ptr<CShape> const & shape)
{
		m_targetShape = shape;
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

void CSelectFrame::UpdateFrame()
{
	SetPoints();
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


void CSelectFrame::SendCommandToReseiver(sf::Event const & event)
{
	if (GetReseiver() == nullptr || m_targetShape == nullptr)
		return;
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		m_oldFrameSize = m_targetShape->GetBoundingRect();
		break;
	case sf::Event::MouseButtonReleased:
		GetReseiver()->ChangeRect(m_targetShape, m_oldFrameSize);
		break;
	default: 
		break;
	}
}