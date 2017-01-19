#pragma once

struct ILayer
{
	virtual void DoClickAction() = 0;
	virtual ~ILayer() = default;
};