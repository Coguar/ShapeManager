#include "stdafx.h"
#include "Layer.h"
#include "Reseiver.h"
#include "TextureCache.h"

CLayer::CLayer(Vec2 const & size, Vec2 const & position)
	: m_rect(position,size)
{
}


CLayer::~CLayer()
{
}

void CLayer::Draw(sf::RenderTarget * window, CTextureCache * cache)
{
	if (window != nullptr)
	{
		auto size = m_rect.size;
		sf::RectangleShape layersRect({ float(size.x), float(size.y) });
		auto position = m_rect.position;
		layersRect.setPosition(float(position.x), float(position.y));
		if (IsTextured() && cache != nullptr)
		{
			layersRect.setTexture(cache->GetTexture(m_texturePath).get());
		}
		layersRect.setFillColor(sf::Color(sf::Uint8(m_color.r), sf::Uint8(m_color.g), sf::Uint8(m_color.b), sf::Uint8(m_color.a)));

		window->draw(layersRect);
	}
}

void CLayer::Update()
{
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

void CLayer::SetTexturePath(std::string const & path)
{
	m_isTextured = true;
	m_texturePath = path;
}

std::string const & CLayer::GetPath() const
{
	return m_texturePath;
}

bool CLayer::IsTextured() const
{
	return m_isTextured;
}
