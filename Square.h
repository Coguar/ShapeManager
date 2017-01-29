#pragma once
#include "AbstractShape.h"

class �Square
	: public CShape
{
public:
	�Square();
	~�Square() = default;
	bool IsPointIntoShape(Vec2 const& point)const override;

	void Draw(sf::RenderTarget * window, CTextureCache * cache) override;
};

