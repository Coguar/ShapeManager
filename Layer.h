#pragma once
#include "EventListener.h"
#include "Rectangle.h"

class CLayer :
	public CEventListener
{
public:
	CLayer(Vec2 const& size = { 0.0, 0.0 }, Vec2 const& position = { 0.0, 0.0 });
	~CLayer();

	void SetColor(SColor const& color);
	SColor GetColor()const;

	CBoundingRect GetBoundingRect() const;
	void SetBoundingRect(CBoundingRect const& rect);

	void SetPosition(Vec2 const& position);
	Vec2 GetPosition() const;

	void SetSize(Vec2 const& size);
	Vec2 GetSize() const;

private:
	SColor m_color;
	CBoundingRect m_rect;
};

