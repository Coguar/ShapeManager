#pragma once
#include "DragPoint.h"

class CSelectFrame :
	public CEventListener
{
public:
	CSelectFrame();
	~CSelectFrame();
	bool OnEvent(sf::Event const& event) override;


	void SetTarget(std::shared_ptr<CShape> const& shape);
	std::vector<std::shared_ptr<CDragPoint>> GetDragPoints() const;
	void ResetTargget();
	bool IsActive() const;
private:
	void SetPoints();

	std::weak_ptr<CShape> m_targetShape;
	std::vector<std::shared_ptr<CDragPoint>> m_dragPoints;
};

