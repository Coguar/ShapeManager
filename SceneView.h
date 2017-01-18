#pragma once
#include "ViewInterface.h"

class CSceneView :public IView
{
public:
	CSceneView(sf::RenderWindow * window);
	~CSceneView();
	void Draw(CLayer * layer) override;
private:
	void DrawLayer(CLayer * layer);
	sf::RenderWindow * m_window;
};

