#pragma once

struct ILayer
{
	virtual void AddChild(ILayer * child) = 0;
	virtual ~ILayer() = default;
};