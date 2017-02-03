#pragma once
#include "EventListener.h"
#include "Rectangle.h"

class CLayer :
	public CEventListener
{
public:
	CLayer(Vec2 const& size = { 0.0, 0.0 }, Vec2 const& position = { 0.0, 0.0 });
	virtual ~CLayer();

	CBoundingRect GetBoundingRect() const;
	virtual void SetBoundingRect(CBoundingRect const& rect);

	virtual void SetPosition(Vec2 const& position);
	Vec2 GetPosition() const;

	virtual void SetSize(Vec2 const& size);
	Vec2 GetSize() const;

private:
	CBoundingRect m_rect;
};

