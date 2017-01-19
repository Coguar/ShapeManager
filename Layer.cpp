#include "stdafx.h"
#include "Layer.h"


CLayer::CLayer(SSize const & size, SCoords const & posizion)
	: CRectangle(posizion, size)
{
}

CLayer::~CLayer()
{
}

void CLayer::AddChild(LayerPtr const & child)
{
	auto localPos = child->GetPosition();
	auto origin = GetPosition();
	child->SecPosition({ localPos.x + origin.x, localPos.y + origin.y });
	m_children.push_back(child);
}

std::vector<std::shared_ptr<CLayer>> const& CLayer::GetChildren() const
{
	return m_children;
}

CLayer * CLayer::GetClickedLayer(SCoords const & mousePos)
{
	CLayer * layer = nullptr;
	if (IsPointIntoRect(mousePos))
	{
		layer = this;
		for (auto &child : m_children)
		{
			auto returnedLayer = child->GetClickedLayer(mousePos);
			if (returnedLayer != nullptr)
			{
				layer = returnedLayer;
				break;
			}
		}
	}
	if (layer == this)
	return layer;
}
