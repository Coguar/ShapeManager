#pragma once
#include "ViewInterface.h"

class CSceneView :	public IView
{
public:
	CSceneView(sf::RenderTarget * window);
	~CSceneView() = default;
	void Draw(CLayer * layer) override;
	void DrawShapes(std::vector<std::shared_ptr<CShape>> const& shapes) override;
	void DrawSelectFrame(std::shared_ptr<CSelectFrame> const& frame) override;

private:
	void DrawCircle(std::shared_ptr<CShape> const& shape);
	void DrawSquare(std::shared_ptr<CShape> const& shape);
	void DrawTriangle(std::shared_ptr<CShape> const& shape);

	void DrawLayer(CLayer * layer);
	sf::RenderTarget * m_target;
};

