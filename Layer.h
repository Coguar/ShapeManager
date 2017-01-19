#pragma once
#include "LayerInterface.h"
#include "Rectangle.h"
#include "Drawable.h"
#include "EventListener.h"
class CLayer 
	: public CRectangle
	, public CDrawable
	, public CEventListener
{
	typedef std::shared_ptr<CLayer> LayerPtr;
public:
	CLayer(SSize const& size = { 0.0, 0.0 }, SCoords const& posizion = {0.0, 0.0});
	~CLayer();
	virtual void AddChild(LayerPtr const & child);
	std::vector<std::shared_ptr<CLayer>> const& GetChildren() const;

	CLayer* GetClickedLayer(SCoords const& mousePos);
private:
	std::vector<std::shared_ptr<CLayer>> m_children;
	
};

