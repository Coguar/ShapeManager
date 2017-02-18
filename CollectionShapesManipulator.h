#pragma once
#include <string>

enum class ShapeType;
struct Vec2;

struct ICollectionShapesManipulator
{
	virtual void AddShape(ShapeType type, Vec2 const& position) = 0;
	virtual void AddPicture(Vec2 const& position, std::string const& path) = 0;
	virtual void DeleteShape(size_t position) = 0;
	virtual void MoveShapeLayer(size_t position, bool isToUp) = 0;

	virtual void RedoCommand() = 0;
	virtual void UndoCommand() = 0;

	virtual void Save(std::string const& path) = 0;
	virtual void Open(std::string const& path) = 0;

	virtual void Clear() = 0;

	virtual Vec2 GetCanvasSize() const = 0;
	virtual ~ICollectionShapesManipulator() = default;
};