#pragma once
#include "Coords.h"
#include "ShapesTypes.h"

class SModelShape
{
public:
	SModelShape() = default;
	SModelShape(ShapeType type, Vec2 const& position = Vec2(), Vec2 const& size = Vec2());
	virtual ~SModelShape() = default;

	void SetRect(Vec2 const& pos, Vec2 const& size);

	ShapeType GetType() const;
	Vec2 GetPosition() const;
	Vec2 GetSize() const;

	signal::Connection DoOnRectChanged(std::function<void(const CBoundingRect&)> const& action);

private:
	boost::signals2::signal<void(const CBoundingRect&)> m_OnRectChange;

	Vec2 m_position;
	Vec2 m_size;
	ShapeType m_type;
};