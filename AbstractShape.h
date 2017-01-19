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
	CAbstractShape(shape::Type type);
	~CAbstractShape() = default;

	shape::Type GetType()const override;
	bool IsPointIntoShape(SCoords const& point)const override;

	bool OnMousePressed(sf::Event::MouseButtonEvent const& event);
	bool OnMouseReleased(sf::Event::MouseButtonEvent const& event);
	bool OnMouseMoved(sf::Event::MouseMoveEvent const& event);
private:
	shape::Type m_type;
	bool m_isSelected = false;
};

