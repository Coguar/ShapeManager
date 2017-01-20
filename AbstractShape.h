#pragma once
#include "Rectangle.h"
#include "Drawable.h"
#include "ShapeInterface.h"
#include "EventListener.h"

class CAbstractShape 
	: public CRectangle
	, public CDrawable
	, public IShape
	, public CEventListener
{
public:
	CAbstractShape(ShapeType type);
	~CAbstractShape() = default;

	ShapeType GetType()const override;
	bool IsPointIntoShape(Vec2 const& point)const override;

	bool OnMousePressed(sf::Event::MouseButtonEvent const& event);
	bool OnMouseReleased(sf::Event::MouseButtonEvent const& event);
	bool OnMouseMoved(sf::Event::MouseMoveEvent const& event);
private:
	ShapeType m_type;
	bool m_isSelected = false;
};

