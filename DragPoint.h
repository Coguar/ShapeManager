#pragma once
#include "Circle.h"

class CDragPoint :
	public CCircle
{
public:
	CDragPoint();
	~CDragPoint();

	void SetConnectedPoint(std::shared_ptr<CDragPoint> const& xPoint, std::shared_ptr<CDragPoint> const& yPoint);
	void SetMinMaxDistanceBetweenPoints(double min, double max);

	Vec2 GetDistantionFromConnections();

	bool OnMouseMoved(sf::Event::MouseMoveEvent const& event) override;

	bool IsPointIntoShape(Vec2 const & point) const override;

private:
	void UpdateConnectedPoints();

	CDragPoint * m_yConnection;
	CDragPoint * m_xConnection;

	double m_maxDistance = MAX_SHAPE_SIZE;
	double m_minDistance = MIN_SHAPE_SIZE;

};

