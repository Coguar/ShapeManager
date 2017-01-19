#include "stdafx.h"
#include "Toolbar.h"


CToolbar::CToolbar()
{
}


CToolbar::~CToolbar()
{
}

void CToolbar::AddChild(LayerPtr const & child)
{
	CLayer::AddChild(child);
	if (GetChildren().size() > 1)
	{
		auto lastLayerPos = GetChildren().back()->GetPosition();
		auto lastLayerSize = GetChildren().back()->GetSize();
		child->SecPosition({ lastLayerPos.x + lastLayerSize.x + m_defaultOffset, lastLayerPos.y });
	}
	else
	{
		child->SecPosition({ m_defaultOffset + GetPosition().x,  m_defaultOffset + GetPosition().y });
	}	
}
