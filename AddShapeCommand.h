#pragma once
#include "MyCommand.h"

class CAddShapeCommand :
	public CCanvasCommand
{
public:
	CAddShapeCommand(std::shared_ptr<SModelShape> const& shape, CCanvas* model);
	~CAddShapeCommand();

	void Execute() override;
	void Unexecute() override;
	void Destroy() override;

private:
	std::shared_ptr<SModelShape> m_shape;
};

