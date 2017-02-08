#pragma once
#include "Layer.h"

class CSolidLayer :
	public CLayer
{
public:
	CSolidLayer(Vec2 const& size = { 0.0, 0.0 }, Vec2 const& position = { 0.0, 0.0 });
	virtual ~CSolidLayer();

	void Draw(sf::RenderTarget * window, CTextureCache * cache) override;

	void SetColor(SColor const& color);
	SColor GetColor()const;

	virtual void SetTexturePath(std::string const& path);
	std::string const& GetPath() const;

	bool IsTextured() const;

private:
	SColor m_color;

	std::string m_texturePath;
	bool m_isTextured = false;
};

