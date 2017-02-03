#include "stdafx.h"
#include "SolidLayer.h"
#include "TextureCache.h"


CSolidLayer::CSolidLayer(Vec2 const & size, Vec2 const & position)
	: CLayer(size, position)
{
}


CSolidLayer::~CSolidLayer()
{
}

void CSolidLayer::Draw(sf::RenderTarget * window, CTextureCache * cache)
{
	if (window != nullptr)
	{
		auto size = GetSize();
		sf::RectangleShape layersRect({ float(size.x), float(size.y) });
		auto position = GetPosition();
		layersRect.setPosition(float(position.x), float(position.y));
		if (IsTextured() && cache != nullptr)
		{
			layersRect.setTexture(cache->GetTexture(m_texturePath).get());
		}
		layersRect.setFillColor(sf::Color(sf::Uint8(m_color.r), sf::Uint8(m_color.g), sf::Uint8(m_color.b), sf::Uint8(m_color.a)));

		window->draw(layersRect);
	}
}

void CSolidLayer::SetColor(SColor const & color)
{
	m_color = color;
}

SColor CSolidLayer::GetColor() const
{
	return m_color;
}

void CSolidLayer::SetTexturePath(std::string const & path)
{
	m_isTextured = true;
	m_texturePath = path;
}

std::string const & CSolidLayer::GetPath() const
{
	return m_texturePath;
}

bool CSolidLayer::IsTextured() const
{
	return m_isTextured;
}
