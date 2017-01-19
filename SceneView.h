#pragma once
#include "ViewInterface.h"
class CSceneView :public IView
{
public:
	CSceneView(sf::RenderWindow * window);
	~CSceneView();
	void Draw(CLayer * layer) override;
	void DrawShapes(CCanvas * canvas) override;
private:
	void DrawCircle(std::shared_ptr<CAbstractShape> const& shape);
	void DrawSquare(std::shared_ptr<CAbstractShape> const& shape);
	void DrawTriangle(std::shared_ptr<CAbstractShape> const& shape);

	void DrawLayer(CLayer * layer);
	sf::RenderWindow * m_window;
};

