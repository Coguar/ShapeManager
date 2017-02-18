#pragma once
#include "Signal.h"
#include <functional>
#include <memory>

class SModelShape;

struct ICanvasSignaller
{
	virtual signal::Connection DoOnShapeAdd(std::function<void(std::shared_ptr<SModelShape>, size_t)> const& action) = 0;
	virtual signal::Connection DoOnShapeDelete(std::function<void(size_t)> const& action) = 0;
	virtual signal::Connection DoOnShapesClear(std::function<void()> const& action) = 0;
	virtual signal::Connection DoOnShapesLayerMove(std::function<void(size_t, bool)> const& action) = 0;
	virtual ~ICanvasSignaller() = default;
};