#pragma once
#include "EventListener.h"
#include "Rectangle.h"

class CTextureCache;

class CLayer :
	public CEventListener
{
public:
	CLayer(Vec2 const& size = { 0.0, 0.0 }, Vec2 const& position = { 0.0, 0.0 });
	virtual ~CLayer();

	virtual void Draw(sf::RenderTarget * window, CTextureCache * cache);
	virtual void Update();

	void SetColor(SColor const& color);
	SColor GetColor()const;

	CBoundingRect GetBoundingRect() const;
	void SetBoundingRect(CBoundingRect const& rect);

	void SetPosition(Vec2 const& position);
	Vec2 GetPosition() const;

	void SetSize(Vec2 const& size);
	Vec2 GetSize() const;

	void SetTexturePath(std::string const& path);
	std::string const& GetPath() const;
	 
	bool IsTextured() const;

private:
	SColor m_color;
	CBoundingRect m_rect;

	std::string m_texturePath;
	bool m_isTextured = false;
};

