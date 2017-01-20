#include "stdafx.h"
#include "SceneView.h"
#include "Ellipse.h"

CSceneView::CSceneView(sf::RenderTarget * window)
	: m_target(window)
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

void CSceneView::DrawShapes(std::vector<std::shared_ptr<CShape>> const& shapes)
{
	for (auto &shape : shapes)
	{
		switch (shape->GetType())
		{
		case ShapeType::Circle:
			DrawCircle(shape);
			break;
		case ShapeType::Triangle:
			DrawTriangle(shape);
			break;
		case ShapeType::Rectangle:
			DrawSquare(shape);
			break;
		default:
			break;
		}
	}
}

void CSceneView::DrawSelectFrame(std::shared_ptr<CSelectFrame> const & frame)
{
	if (frame->IsActive())
	{
		auto points = frame->GetDragPoints();
		for (auto &point : points)
		{
			DrawCircle(point);
		}
		Vec2 position(points[0]->GetPosition().x + points[0]->GetSize().x / 2, points[0]->GetPosition().y + points[0]->GetSize().y / 2);
		Vec2 size(std::abs(points[0]->GetPosition().x - points[2]->GetPosition().x), std::abs(points[0]->GetPosition().y - points[2]->GetPosition().y));
		DrawFrame(position, size);
	}
}

void CSceneView::DrawCircle(std::shared_ptr<CShape> const & shape)
{
	auto size = shape->GetSize();
	EllipseShape ellipse({ float(size.x / 2.0), float(size.y / 2.0) });
	ellipse.setPosition(sf::Vector2f( float(shape->GetPosition().x), float(shape->GetPosition().y)));
	auto color = shape->GetColor();
	ellipse.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
	ellipse.setOutlineThickness(1.f);
	ellipse.setOutlineColor(sf::Color::Black);
	m_target->draw(ellipse);
}

void CSceneView::DrawSquare(std::shared_ptr<CShape> const & shape)
{
	auto rect = shape->GetBoundingRect();
	sf::RectangleShape rectangle({ float(rect.size.x), float(rect.size.y)});
	rectangle.setPosition({ float(rect.position.x), float(rect.position.y) });
	auto color = shape->GetColor();
	rectangle.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
	rectangle.setOutlineThickness(1.f);
	rectangle.setOutlineColor(sf::Color::Black);
	m_target->draw(rectangle);
}

void CSceneView::DrawTriangle(std::shared_ptr<CShape> const & shape)
{
	auto rect = shape->GetBoundingRect();

	sf::ConvexShape convex(3);
	convex.setPoint(0, { float(rect.position.x), float(rect.position.y + rect.size.y) });
	convex.setPoint(1, { float(rect.position.x + rect.size.x / 2.f), float(rect.position.y) });
	convex.setPoint(2, { float(rect.position.x + rect.size.x), float(rect.position.y + rect.size.y) });
	auto color = shape->GetColor();
	convex.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
	convex.setOutlineThickness(1.f);
	convex.setOutlineColor(sf::Color::Black);
	m_target->draw(convex);
}

void CSceneView::DrawFrame(Vec2 const & position, Vec2 const & size)
{
	sf::RectangleShape frame({ float(size.x), float(size.y) });
	frame.setFillColor(sf::Color(0, 0, 0, 0));
	frame.setOutlineThickness(1.5f);
	frame.setOutlineColor(sf::Color::Green);
	frame.setPosition({ float(position.x), float(position.y) });
	m_target->draw(frame);
}

void CSceneView::DrawLayer(CLayer * layer)
{
	auto size = layer->GetSize();
	sf::RectangleShape layersRect({ float(size.x), float(size.y)});
	auto color = layer->GetColor();
	layersRect.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
	auto position = layer->GetPosition();
	layersRect.setPosition(float(position.x), float(position.y));
	m_target->draw(layersRect);
}
