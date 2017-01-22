#pragma once
#include "MyCommand.h"

class CMoveShapeCommand :
	public CMyCommand
{
public:
	CMoveShapeCommand(std::shared_ptr<CShape> const& shape, Vec2 const& oldPos);
	~CMoveShapeCommand();

	void Execute() override;
	void Unexecute() override;
private:
	Vec2 m_oldPos;
	Vec2 m_newPos;

	std::shared_ptr<CShape> m_shape;
};

