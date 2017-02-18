#pragma once
#include <functional>
#include <memory>
#include "Signal.h"

class CShapePresenter;

struct IModelSignalsConnector
{
	virtual signal::Connection DoOnShapeAdded(std::function<void(std::shared_ptr<CShapePresenter>, size_t)> const& action) = 0;
	virtual signal::Connection DoOnShapeDelete(std::function<void(size_t)> const& action) = 0;
	virtual signal::Connection DoOnShapesClear(std::function<void()> const& action) = 0;
	virtual signal::Connection DoOnSavedStateChanged(std::function<void(bool)> const& action) = 0;
	virtual signal::Connection DoOnShapesLayerMove(std::function<void(size_t, bool)> const& action) = 0;
	virtual ~IModelSignalsConnector() = default;
};