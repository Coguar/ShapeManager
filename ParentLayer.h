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

	virtual void DispatchEvent(sf::Event const& event);
	void Update() override;
	void Draw(sf::RenderTarget * window, CTextureCache * cache) override;
private:
	std::vector<CLayerPtr> m_children;

};

