#include "stdafx.h"
#include "Layer.h"


CLayer::CLayer(SCoords const & posizion, SSize const & size)
	: CRectangle(posizion, size)
{
}

CLayer::~CLayer()
{
}

void CLayer::AddChild(CLayer * child)
{
	auto localPos = child->GetPosition();
	auto origin = GetPosition();
	child->SecPosition({ localPos.x + origin.x, localPos.y + origin.y });
	m_children.push_back(std::make_shared<CLayer>(*child));
}

std::vector<std::shared_ptr<CLayer>> const& CLayer::GetChildren() const
{
	return m_children;
}
