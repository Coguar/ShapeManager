#pragma once
#include "AbstractShape.h"

class CSelectFrame :
	public CEventListener
{
public:
	CSelectFrame();
	~CSelectFrame();
	void SetTarget(std::shared_ptr<CShape> const& shape);
	std::vector<std::shared_ptr<CShape>> GetDragPoints() const;
	void ResetTargget();
	bool IsActive();
private:
	void SetPoints();

	std::weak_ptr<CShape> m_targetShape;
	std::vector<std::shared_ptr<CShape>> m_dragPoints;
};

