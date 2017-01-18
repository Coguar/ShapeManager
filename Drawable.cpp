#include "stdafx.h"
#include "Drawable.h"

void CDrawable::SetColor(SColor const & color)
{
	m_color = color;
}

SColor CDrawable::GetColor() const
{
	return m_color;
}
