#pragma once
#include "CommandInterface.h"
#include "Canvas.h"

class CCanvasCommand :
	public ICommand
{
public:
	CCanvasCommand(CCanvas* model);
	~CCanvasCommand();
protected:
	CCanvas * m_model = nullptr;
};

