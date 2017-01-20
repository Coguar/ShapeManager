#pragma once
#include "Layer.h"

const enum class ShapeType
{
	Circle = 0,
	Triangle,
	Rectangle,
};

class CShape : public CLayer
{
public:
	CShape(ShapeType type);
	~CShape() = default;

	ShapeType GetType()const;
	virtual bool IsPointIntoShape(Vec2 const& point)const;

	bool OnMousePressed(sf::Event::MouseButtonEvent const& event);
	bool OnMouseReleased(sf::Event::MouseButtonEvent const& event);
	bool OnMouseMoved(sf::Event::MouseMoveEvent const& event);
private:
	ShapeType m_type;
	bool m_isSelected = false;
	bool m_isMoved = false;
	Vec2 m_offset;
};

