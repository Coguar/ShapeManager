#pragma once
#include "LayerInterface.h"
#include "Rectangle.h"
#include "Drawable.h"
class CLayer : public CRectangle, public CDrawable, public ILayer
{
public:
	CLayer(SSize const& size = { 0.0, 0.0 }, SCoords const& posizion = {0.0, 0.0});
	~CLayer();
	void AddChild(CLayer * child);
	std::vector<std::shared_ptr<CLayer>> const& GetChildren() const;

	CLayer* GetClickedLayer(SCoords const& mousePos);
	void DoClickAction() override;
private:
	//bool IsPointIntoThis(SCoords const& point);

	std::vector<std::shared_ptr<CLayer>> m_children;
	
};

