#include "stdafx.h"
#include "DragPoint.h"

namespace
{
	bool InRange(double number, double min, double max)
	{
		return number >= min && number <= max;
	}
}

CDragPoint::CDragPoint()
{
}


CDragPoint::~CDragPoint()
{
}

void CDragPoint::SetConnectedPoint(std::shared_ptr<CDragPoint> const & xPoint, std::shared_ptr<CDragPoint> const & yPoint)
{
	m_xConnection = xPoint;
	m_yConnection = yPoint;
}

void CDragPoint::SetMinMaxDistanceBetweenPoints(double min, double max)
{
	m_maxDistance = max;
	m_minDistance = min;
}

Vec2 CDragPoint::GetDistantionFromConnections()
{
	auto xConnectionPos = m_xConnection->GetPosition();
	auto yConnectionPos = m_yConnection->GetPosition();
	return Vec2(abs(GetPosition().x - xConnectionPos.x), abs(GetPosition().y - yConnectionPos.y));
}

bool CDragPoint::OnMouseMoved(sf::Event::MouseMoveEvent const & event)
{
	auto oldPosition = GetPosition();
	CShape::OnMouseMoved(event);
	auto position = GetPosition();




	if (!InRange(std::abs(position.x - m_xConnection->GetPosition().x), m_minDistance, m_maxDistance) 
		|| std::abs(oldPosition.x - position.x) >= m_minDistance)
	{
		position.x = oldPosition.x;
	}
	if (!InRange(std::abs(position.y - m_yConnection->GetPosition().y), m_minDistance, m_maxDistance)
		|| std::abs(oldPosition.y - position.y) >= m_minDistance)
	{
		position.y = oldPosition.y;
	}
	SetPosition(position);
	UpdateConnectedPoints();
	return oldPosition.x != position.x || oldPosition.y != position.y;
}

void CDragPoint::UpdateConnectedPoints()
{
	auto position = GetPosition();
	auto sharedY = m_yConnection;
	sharedY->SetPosition({position.x, sharedY->GetPosition().y});
	auto sharedX = m_xConnection;
	sharedX->SetPosition({ sharedX->GetPosition().x, position.y });
}

bool CDragPoint::IsPointIntoShape(Vec2 const & point) const
{
	auto position = GetPosition();
	Vec2 radius(GetSize().x / 2.0, GetSize().y / 2.0);
	Vec2 origin(position.x + radius.x, position.y + radius.y);
	Vec2 pointLockalPos(point.x - origin.x, point.y - origin.y);

	return ((pow(pointLockalPos.x, 2) / pow(radius.x, 2)) + (pow(pointLockalPos.y, 2) / pow(radius.y, 2))) <= 1;
}