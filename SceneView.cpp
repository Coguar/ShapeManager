#include "stdafx.h"
#include "SceneView.h"


CSceneView::CSceneView(sf::RenderWindow * window)
	: m_window(window)
{
}

CSceneView::~CSceneView()
{
}

void CSceneView::DrawLayer(CLayer * layer)
{
	auto size = layer->GetSize();
	sf::RectangleShape layersRect({ size.x, size.y});
	auto color = layer->GetColor();
	layersRect.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
	auto position = layer->GetPosition();
	layersRect.setPosition(position.x, position.y);
	m_window->draw(layersRect);
}
