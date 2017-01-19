#include "stdafx.h"
#include "SceneView.h"
#include "Ellipse.h"

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

void CSceneView::DrawShapes(CCanvas * canvas)
{
	for (auto &shape : canvas->GetShapes())
	{
		switch (shape->GetType())
		{
		default:
			break;
		}
	}
}

void CSceneView::DrawCircle(std::shared_ptr<CAbstractShape> const & shape)
{
	
}

void CSceneView::DrawSquare(std::shared_ptr<CAbstractShape> const & shape)
{
}

void CSceneView::DrawTriangle(std::shared_ptr<CAbstractShape> const & shape)
{
}

void CSceneView::DrawLayer(CLayer * layer)
{
	auto size = layer->GetSize();
	sf::RectangleShape layersRect({ float(size.x), float(size.y)});
	auto color = layer->GetColor();
	layersRect.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
	auto position = layer->GetPosition();
	layersRect.setPosition(float(position.x), float(position.y));
	m_window->draw(layersRect);
}
