#pragma once
#include "MyCommand.h"

class CAddShapeCommand :
	public CMyCommand
{
public:
	CAddShapeCommand(std::shared_ptr<SModelShape> const& shape, CDomainModel* model);
	~CAddShapeCommand();

	void Execute() override;
	void Unexecute() override;

private:
	std::shared_ptr<SModelShape> m_shape;
};

