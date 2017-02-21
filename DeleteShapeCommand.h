#pragma once
#include "MyCommand.h"

class CDeleteShapeCommand :
	public CCanvasCommand
{
public:
	CDeleteShapeCommand(size_t position, CCanvas* model);
	~CDeleteShapeCommand();

	void Execute() override;
	void Unexecute() override;
	void Destroy() override;
private:
	std::shared_ptr<SModelShape> m_shape;
	size_t m_shapePosition = 0;
};

