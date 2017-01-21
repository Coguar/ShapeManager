#pragma once
#include "Layer.h"

class CParentLayer;
using CLayerPtr = std::shared_ptr<CParentLayer>;

class CParentLayer : public CLayer
{
public:
	CParentLayer(Vec2 const& size = { 0.0, 0.0 }, Vec2 const& position = {0.0, 0.0});
	virtual ~CParentLayer();
	virtual void AddChild(CLayerPtr const & child);
	std::vector<CLayerPtr> const& GetChildren() const;

	void DispatchEvent(sf::Event const& event);
private:
	std::vector<CLayerPtr> m_children;

};

