#pragma once
#include "DragPoint.h"
#include "ViewEvent.h"

class CSelectFrame :
	public CEventListener
{
public:
	CSelectFrame();
	~CSelectFrame();
	bool OnEvent(sf::Event const& event) override;

	void SetTarget(std::shared_ptr<CShape> const& shape, size_t num);
	std::shared_ptr<CShape> const& GetTarget() const;

	CBoundingRect const& GetTargetRect() const;

	std::vector<std::shared_ptr<CDragPoint>> GetDragPoints() const;
	void ResetTargget();
	bool IsActive() const;

	void UpdateFrame();
	void DrawFrame(sf::RenderTarget * window);

	SEvent GetLastEvent();

private:
	void SetPoints();
	void OnResizeFrame(sf::Event const & event);
	CBoundingRect m_oldFrameSize;

	std::shared_ptr<CShape> m_targetShape;
	std::vector<std::shared_ptr<CDragPoint>> m_dragPoints;

	SEvent m_event;
};

