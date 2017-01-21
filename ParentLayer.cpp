#include "stdafx.h"
#include "ParentLayer.h"


CParentLayer::CParentLayer(Vec2 const & size, Vec2 const & position)
	: CLayer(size, position)
{
}

CParentLayer::~CParentLayer()
{
}

void CParentLayer::AddChild(CLayerPtr const & child)
{
	auto rect = child->GetBoundingRect();
	child->SetPosition({ rect.position.x + GetBoundingRect().position.x, rect.position.y + GetBoundingRect().position.y });
	m_children.push_back(child);
}

std::vector<CLayerPtr> const& CParentLayer::GetChildren() const
{
	return m_children;
}

void CParentLayer::DispatchEvent(sf::Event const & event)
{
	OnEvent(event);
	for (auto &child : m_children)
	{
		child->DispatchEvent(event);
	}
}
