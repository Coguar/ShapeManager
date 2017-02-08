#include "stdafx.h"
#include "MyCommand.h"


CCanvasCommand::CCanvasCommand(IShapeCollection* model)
	: m_model(model)
{
}


CCanvasCommand::~CCanvasCommand()
{
}
