#pragma once
#include "Rectangle.h"
#include "Drawable.h"
#include "EventListener.h"

class CLayer;
using CLayerPtr = std::shared_ptr<CLayer>;

class CLayer 
	: //public CBoundingRect
	 public CEventListener
{
public:
	CLayer(Vec2 const& size = { 0.0, 0.0 }, Vec2 const& position = {0.0, 0.0});
	~CLayer();
	virtual void AddChild(CLayerPtr const & child);
	std::vector<CLayerPtr> const& GetChildren() const;

	void DispatchEvent(sf::Event const& event);
	CLayer* GetClickedLayer(Vec2 const& mousePos);

	void SetColor(SColor const& color);
	SColor GetColor()const;

	CBoundingRect GetBoundingRect() const;
	void SetBoundingRect(CBoundingRect const& rect);

	void SetPosition(Vec2 const& position);
	Vec2 GetPosition() const;

	void SetSize(Vec2 const& size);
	Vec2 GetSize() const;
private:
	std::vector<CLayerPtr> m_children;
	SColor m_color;
	CBoundingRect m_rect;
};

