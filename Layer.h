#pragma once
#include "LayerInterface.h"
#include "Rectangle.h"
#include "Drawable.h"
class CLayer : public CRectangle, public CDrawable, public ILayer
{
	typedef std::shared_ptr<CLayer> LayerPtr;
public:
	CLayer(SSize const& size = { 0.0, 0.0 }, SCoords const& posizion = {0.0, 0.0});
	~CLayer();
	virtual void AddChild(LayerPtr const & child);
	std::vector<std::shared_ptr<CLayer>> const& GetChildren() const;

	CLayer* GetClickedLayer(SCoords const& mousePos);
	void DoClickAction() override;
private:
	std::vector<std::shared_ptr<CLayer>> m_children;
	
};

