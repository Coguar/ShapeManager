#pragma once
#include "Coords.h"
#include "ShapesTypes.h"

class SModelShape
{
	SModelShape() = default;
	SModelShape(ShapeType type, Vec2 const& position, Vec2 const& size);

	void SetRect(Vec2 const& pos, Vec2 const& size);

	ShapeType GetType() const;
	Vec2 GetPosition() const;
	Vec2 GetSize() const;

	void DoOnRectChanged(std::function<void(Vec2, Vec2)> const& action);

private:
	boost::signals2::signal<void(Vec2, Vec2)> m_OnRectChange;

	Vec2 m_position;
	Vec2 m_size;
	ShapeType m_type;
};