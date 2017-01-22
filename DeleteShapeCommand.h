#pragma once
#include "MyCommand.h"
class CDeleteShapeCommand :
	public CMyCommand
{
public:
	CDeleteShapeCommand(std::shared_ptr<CShape> const& shape, size_t position);
	~CDeleteShapeCommand();

	void Execute() override;
	void Unexecute() override;
private:
	std::shared_ptr<CShape> m_shape;
	size_t m_shapePosition = 0;
};

