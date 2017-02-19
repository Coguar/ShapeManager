#pragma once
#include <string>
#include <memory>
#include "Signal.h"

class SModelShape;
enum class ShapeType;
struct Vec2;

struct ICollectionShapesManipulator
{
	virtual void AddShape(ShapeType type, Vec2 const& position) = 0;
	virtual void AddPicture(Vec2 const& position, std::string const& path) = 0;
	virtual void DeleteShape(size_t position) = 0;
	virtual void MoveShapeLayer(size_t position, bool isToUp) = 0;

	virtual signal::Connection DoOnShapeAdded(std::function<void(std::shared_ptr<SModelShape>, size_t)> const& action) = 0;
	virtual signal::Connection DoOnShapeDelete(std::function<void(size_t)> const& action) = 0;
	virtual signal::Connection DoOnShapesClear(std::function<void()> const& action) = 0;
	virtual signal::Connection DoOnSavedStateChanged(std::function<void(bool)> const& action) = 0;
	virtual signal::Connection DoOnShapesLayerMove(std::function<void(size_t, bool)> const& action) = 0;
	virtual signal::Connection DoOnResourceBecomingUnusable(std::function<void(std::string)> const & action) = 0;

	virtual void Clear() = 0;

	virtual Vec2 GetCanvasSize() const = 0;
	virtual ~ICollectionShapesManipulator() = default;
};