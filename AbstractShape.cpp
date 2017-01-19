#include "stdafx.h"
#include "AbstractShape.h"

CAbstractShape::CAbstractShape(shape::Type type)
	: m_type(type)
{}

shape::Type CAbstractShape::GetType() const
{
	return m_type;
}

bool CAbstractShape::IsPointIntoShape(SCoords const & point) const
{
	return false;
}
