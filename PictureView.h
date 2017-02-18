#pragma once
#include "Square.h"
class CPictureView :
	public ÑSquare
{
public:
	CPictureView();
	~CPictureView();
	void Draw(sf::RenderTarget * window, CTextureCache * cache) override;
};

