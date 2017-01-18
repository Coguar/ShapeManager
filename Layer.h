#pragma once
#include "LayerInterface.h"
#include "Rectangle.h"
#include "Drawable.h"
class CLayer : public CRectangle, CDrawable
{
public:
	CLayer(SCoords const& posizion = {0.0, 0.0}, SSize const& size = { 0.0, 0.0 });
	~CLayer();
	void AddChild(CLayer * child);
private:
	std::vector<std::shared_ptr<CLayer>> m_children;
	
};

