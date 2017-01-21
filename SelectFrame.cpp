#include "stdafx.h"
#include "SelectFrame.h"


CSelectFrame::CSelectFrame()
{
	CDragPoint point;
	point.SetColor(SColor(255, 0, 0, 255));
	point.SetSize({ 10.0, 10.0 });
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
		if (point->OnEvent(event))
		{
			m_targetShape.lock()->SetSize(m_dragPoints[0]->GetDistantionFromConnections());
			auto pointPos = m_dragPoints[0]->GetPosition();
			auto pointSize = m_dragPoints[0]->GetSize();
			m_targetShape.lock()->SetPosition({ pointPos.x + pointSize.x / 2.0,  pointPos.y + pointSize.y / 2.0 });
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
	return !m_targetShape.expired();
}

CBoundingRect const & CSelectFrame::GetTargetRect() const
{
	return m_targetShape.lock()->GetBoundingRect();
}

void CSelectFrame::SetPoints()
{
	if (!m_targetShape.expired())
	{
		auto rect = m_targetShape.lock()->GetBoundingRect();
		auto pointRadius = m_dragPoints[0]->GetBoundingRect().size.x / 2.0;
		m_dragPoints[0]->SetPosition({ rect.position.x - pointRadius, rect.position.y - pointRadius });
		m_dragPoints[1]->SetPosition({ rect.position.x + rect.size.x - pointRadius, rect.position.y - pointRadius });
		m_dragPoints[2]->SetPosition({ rect.position.x - pointRadius, rect.position.y + rect.size.y - pointRadius });
		m_dragPoints[3]->SetPosition({ rect.position.x + rect.size.x - pointRadius, rect.position.y + rect.size.y - pointRadius });
	}
}
