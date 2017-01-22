#pragma once
#include "MyCommand.h"
class CAddShapeCommand :
	public CMyCommand
{
public:
	CAddShapeCommand(std::shared_ptr<CShape> const& shape);
	~CAddShapeCommand();

	void Execute() override;
	void Unexecute() override;

private:
	std::shared_ptr<CShape> m_shape;
};

