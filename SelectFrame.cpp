#include "stdafx.h"
#include "SelectFrame.h"


CSelectFrame::CSelectFrame()
{
	CShape point(ShapeType::Circle);
	point.SetColor(SColor(255, 0, 0, 255));
	point.SetSize({ 10.0, 10.0 });
	for (size_t i = 0; i < 4; ++i)
	{
		m_dragPoints.push_back(std::make_shared<CShape>(point));
	}
}


CSelectFrame::~CSelectFrame()
{
}

void CSelectFrame::SetTarget(std::shared_ptr<CShape> const & shape)
{
		m_targetShape = shape;
		SetPoints();
}

std::vector<std::shared_ptr<CShape>> CSelectFrame::GetDragPoints() const
{
	return m_dragPoints;
}

void CSelectFrame::ResetTargget()
{
	m_targetShape.reset();
}

bool CSelectFrame::IsActive()
{
	return !m_targetShape.expired();
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
