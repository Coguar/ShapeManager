#pragma once
#include "AbstractCommand.h"
#include "Canvas.h"

class CCanvasCommand :
	public CAbstractCommand
{
public:
	CCanvasCommand(IShapeCollection* model);
	~CCanvasCommand();
	void Destroy() override;

protected:
	IShapeCollection * m_model = nullptr;
};

