#pragma once
#include "AbstractShape.h"
class CDragPoint :
	public CShape
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

	std::weak_ptr<CDragPoint> m_yConnection;
	std::weak_ptr<CDragPoint> m_xConnection;

	double m_maxDistance = 120.0;
	double m_minDistance = 30.0;

};

