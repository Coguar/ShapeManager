#pragma once
#include <functional>
#include <memory>

class SModelShape;

struct ICanvasSignaller
{
	virtual void DoOnShapeAdd(std::function<void(std::shared_ptr<SModelShape>, size_t)> const& action) = 0;
	virtual void DoOnShapeDelete(std::function<void(size_t)> const& action) = 0;
	virtual void DoOnShapesClear(std::function<void()> const& action) = 0;
	virtual ~ICanvasSignaller() = default;
};