#pragma once
#include "ParentLayer.h"
class CToolbar :
	public CParentLayer
{
	typedef std::shared_ptr<CParentLayer> LayerPtr;
public:
	CToolbar();
	~CToolbar();
	void AddChild(LayerPtr const & child) override;

private:
	const double m_defaultOffset = 10.0;
};

