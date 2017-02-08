#pragma once
#include "CommandInterface.h"
#include "Canvas.h"

class CCanvasCommand :
	public ICommand
{
public:
	CCanvasCommand(IShapeCollection* model);
	~CCanvasCommand();
protected:
	IShapeCollection * m_model = nullptr;
};

