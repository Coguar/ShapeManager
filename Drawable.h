#pragma once
#include "DrawableInterface.h"

class CDrawable : public IDrawable
{
public:
	CDrawable() = default;
	~CDrawable() = default;
	void SetColor(SColor const& color) override;
	SColor GetColor()const override;

private:
	SColor m_color;
};

