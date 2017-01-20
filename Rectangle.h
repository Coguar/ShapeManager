#pragma once
#include "RectangleInterface.h"

class CRectangle //: public IRectangle
{
public:
	CRectangle() = default;
	CRectangle(Vec2 const& positon, Vec2 const& size);
	~CRectangle() = default;

	bool IsPointIntoRect(Vec2 const& point)const;
	Vec2 GetSize() const;
	Vec2 GetPosition() const;
	void SetSize(Vec2 const& size);
	void SecPosition(Vec2 const& position);

private:

	Vec2 m_position;
	Vec2 m_size;
};

