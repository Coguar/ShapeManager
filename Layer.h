#pragma once
#include "LayerInterface.h"
#include "Rectangle.h"
#include "Drawable.h"
class CLayer : public CRectangle, public CDrawable
{
public:
	CLayer(SCoords const& posizion = {0.0, 0.0}, SSize const& size = { 0.0, 0.0 });
	~CLayer();
	void AddChild(CLayer * child);
	std::vector<std::shared_ptr<CLayer>> const& GetChildren() const;
private:
	std::vector<std::shared_ptr<CLayer>> m_children;
	
};

