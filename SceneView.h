#pragma once
#include "ViewInterface.h"
#include "TextureCache.h"
class CSceneView :	public IView
{
public:
	CSceneView(sf::RenderTarget * window);
	~CSceneView() = default;
	void Draw(CParentLayer * layer) override;
	void DrawShapes(std::vector<std::shared_ptr<CShape>> const& shapes) override;
	void DrawSelectFrame(std::shared_ptr<CSelectFrame> const& frame) override;

private:
	void DrawCircle(std::shared_ptr<CShape> const& shape);
	void DrawSquare(std::shared_ptr<CShape> const& shape);
	void DrawTriangle(std::shared_ptr<CShape> const& shape);
	void DrawFrame(Vec2 const& position, Vec2 const& size);
	void DrawLayer(CParentLayer * layer);
	sf::RenderTarget * m_target;

	std::shared_ptr<CTextureCache> m_cache;
};

