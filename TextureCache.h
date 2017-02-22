#pragma once
class CTextureCache
{
public:
	CTextureCache();
	~CTextureCache();
	std::shared_ptr<sf::Texture> const& GetTexture(std::string const& path);

private:
	std::map<std::string, std::shared_ptr<sf::Texture>> m_cache;
	std::shared_ptr<sf::Texture> m_defaultTexture;
};

