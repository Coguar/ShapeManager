#pragma once
#include "ParentLayer.h"
#include "ShapesTypes.h"
//const enum class ShapeType
//{
//	Circle = 0,
//	Triangle,
//	Rectangle,
//};

class CShape 
	: public CLayer
{
public:
	CShape(ShapeType type);
	~CShape() = default;

	ShapeType GetType()const;
	virtual bool IsPointIntoShape(Vec2 const& point)const;

	bool OnMousePressed(sf::Event::MouseButtonEvent const& event) override;
	bool OnMouseReleased(sf::Event::MouseButtonEvent const& event) override;
	bool OnMouseMoved(sf::Event::MouseMoveEvent const& event) override;

	bool IsMooved() const;
	void SetAllowableArea(CBoundingRect const& rect);
	CBoundingRect const& GetAllowableArea() const;
private:
	void SetInAllowableArea();

	ShapeType m_type;
	bool m_isMoved = false;
	Vec2 m_offset;

	CBoundingRect m_allowableArea;
};

