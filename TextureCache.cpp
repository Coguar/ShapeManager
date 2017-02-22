#include "stdafx.h"
#include "TextureCache.h"


CTextureCache::CTextureCache()
{
	m_defaultTexture = std::make_shared<sf::Texture>();
	m_defaultTexture->loadFromFile(DEFAULT_TEXTURE);
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
		if (!boost::filesystem::exists(boost::filesystem::path(path)) || !boost::filesystem::is_regular_file(path))
		{
			m_cache.insert({ path, m_defaultTexture });
			return m_defaultTexture;
		}
		else
		{
			auto texture = std::make_shared<sf::Texture>();
			texture->loadFromFile(path);
			m_cache.insert({ path, texture });
			return m_cache.find(path)->second;
		}
	}
}
