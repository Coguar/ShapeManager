#include "stdafx.h"
#include "TextureCache.h"


CTextureCache::CTextureCache()
{
}


CTextureCache::~CTextureCache()
{
}

std::shared_ptr<sf::Texture> const & CTextureCache::GetTexture(std::string const & path)
{
	if (m_cache.find(path) != m_cache.end())
	{
		return m_cache.find(path)->second;
	}
	else
	{
		auto texture = std::make_shared<sf::Texture>();
		texture->loadFromFile(path);
		m_cache.insert({ path, texture });
		return texture;
	}
}
