#include "stdafx.h"
#include "Layer.h"
#include "Reseiver.h"

CLayer::CLayer(Vec2 const & size, Vec2 const & position)
	: m_rect(position,size)
{
}


CLayer::~CLayer()
{
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
