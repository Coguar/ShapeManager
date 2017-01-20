#include "stdafx.h"
#include "Layer.h"


CLayer::CLayer(Vec2 const & size, Vec2 const & position)
	: CRectangle(position, size)
{
}

CLayer::~CLayer()
{
}

void CLayer::AddChild(CLayerPtr const & child)
{
	auto localPos = child->GetPosition();
	auto origin = GetPosition();
	child->SecPosition({ localPos.x + origin.x, localPos.y + origin.y });
	m_children.push_back(child);
}

std::vector<CLayerPtr> const& CLayer::GetChildren() const
{
	return m_children;
}

void CLayer::DispatchEvent(sf::Event const & event)
{
	OnEvent(event);
	for (auto &child : m_children)
	{
		child->DispatchEvent(event);
	}
}

CLayer * CLayer::GetClickedLayer(Vec2 const & mousePos)
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
