#pragma once

struct IRectangle
{
	virtual bool IsPointIntoRect(Vec2 const& point)const = 0;
	virtual Vec2 GetSize()const = 0;
	virtual Vec2 GetPosition()const = 0;
	virtual void SetSize(Vec2 const& size) = 0;
	virtual void SecPosition(Vec2 const& position) = 0;
	virtual ~IRectangle() = default;
};