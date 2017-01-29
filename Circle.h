#pragma once
#include "AbstractShape.h"

class CCircle :
	public CShape
{
public:
	CCircle();
	~CCircle() = default;
	bool IsPointIntoShape(Vec2 const& point)const override;

	void Draw(sf::RenderTarget * window, CTextureCache * cache) override;
};

