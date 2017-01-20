#pragma once
#include "Rectangle.h"
#include "Drawable.h"
#include "EventListener.h"

class CLayer;
using CLayerPtr = std::shared_ptr<CLayer>;

class CLayer 
	: public CRectangle
	, public CDrawable
	, public CEventListener
{
public:
	CLayer(Vec2 const& size = { 0.0, 0.0 }, Vec2 const& position = {0.0, 0.0});
	~CLayer();
	virtual void AddChild(CLayerPtr const & child);
	std::vector<CLayerPtr> const& GetChildren() const;

	void DispatchEvent(sf::Event const& event);
	CLayer* GetClickedLayer(Vec2 const& mousePos);

private:
	std::vector<CLayerPtr> m_children;
};

