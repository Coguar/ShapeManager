#pragma once
#include "Layer.h"

struct IView
{
	virtual void Draw(CLayer * layer) = 0;
	virtual ~IView() = default;
};