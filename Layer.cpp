#include "stdafx.h"
#include "Layer.h"


CLayer::CLayer(Vec2 const & size, Vec2 const & position)
	: m_rect(CBoundingRect(position, size))
{
}

CLayer::~CLayer()
{
}

void CLayer::AddChild(CLayerPtr const & child)
{
	auto rect = child->GetBoundingRect();
	child->SetPosition({ rect.position.x + m_rect.position.x, rect.position.y + m_rect.position.y });
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
	if (m_rect.IsPointInRect(mousePos))
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

void CLayer::SetColor(SColor const & color)
{
	m_color = color;
}

SColor CLayer::GetColor() const
{
	return m_color;
}

CBoundingRect CLayer::GetBoundingRect() const
{
	return m_rect;
}

void CLayer::SetBoundingRect(CBoundingRect const & rect)
{
	m_rect = rect;
}

void CLayer::SetPosition(Vec2 const & position)
{
	m_rect.position = position;
}

Vec2 CLayer::GetPosition() const
{
	return m_rect.position;
}

void CLayer::SetSize(Vec2 const & size)
{
	m_rect.size = size;
}

Vec2 CLayer::GetSize() const
{
	return m_rect.size;
}
