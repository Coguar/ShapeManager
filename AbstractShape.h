#pragma once
#include "Rectangle.h"
#include "Drawable.h"
#include "ShapeInterface.h"
class CAbstractShape 
	: public CRectangle
	, public CDrawable
	, public IShape
{
public:
	CAbstractShape(shape::Type type);
	~CAbstractShape() = default;
	shape::Type GetType()const override;
	bool IsPointIntoShape(SCoords const& point)const override;

private:
	shape::Type m_type;
};

