#pragma once
#include "Layer.h"
class CToolbar :
	public CLayer
{
	typedef std::shared_ptr<CLayer> LayerPtr;
public:
	CToolbar();
	~CToolbar();
	void AddChild(LayerPtr const & child) override;

private:
	const double m_defaultOffset = 10.0;
};

