#pragma once
#include "DragPoint.h"
#include "Reseiver.h"

class CSelectFrame :
	public CEventListener
{
public:
	CSelectFrame();
	~CSelectFrame();
	bool OnEvent(sf::Event const& event) override;


	void SetTarget(std::shared_ptr<CShape> const& shape);
	std::shared_ptr<CShape> const& GetTarget() const;

	std::vector<std::shared_ptr<CDragPoint>> GetDragPoints() const;
	void ResetTargget();
	bool IsActive() const;

	CBoundingRect const& GetTargetRect() const;

	void UpdateFrame();
private:
	void SetPoints();
	void SendCommandToReseiver(sf::Event const& event);
	CBoundingRect m_oldFrameSize;

	std::shared_ptr<CShape> m_targetShape;
	std::vector<std::shared_ptr<CDragPoint>> m_dragPoints;
};

