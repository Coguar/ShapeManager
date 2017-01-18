#include "stdafx.h"
#include "SceneView.h"


CSceneView::CSceneView(sf::RenderWindow * window)
	: m_window(window)
{
}

CSceneView::~CSceneView()
{
}

void CSceneView::Draw(CLayer * layer)
{
	DrawLayer(layer);
	for (auto &child : layer->GetChildren())
	{
		Draw(child.get());
	}
}

void CSceneView::DrawLayer(CLayer * layer)
{
	auto size = layer->GetSize();
	sf::RectangleShape layersRect({ float(size.x), float(size.y)});
	auto color = layer->GetColor();
	layersRect.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
	auto position = layer->GetPosition();
	layersRect.setPosition(position.x, position.y);
	m_window->draw(layersRect);
}
