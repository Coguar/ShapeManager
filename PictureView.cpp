#include "stdafx.h"
#include "PictureView.h"


CPictureView::CPictureView()
{
}


CPictureView::~CPictureView()
{
}

void CPictureView::Draw(sf::RenderTarget * window, CTextureCache * cache)
{
	CSolidLayer::Draw(window, cache);
}
