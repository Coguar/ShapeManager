#pragma once
#include "MyCommand.h"

class CChangeLayerCommand :
	public CCanvasCommand
{
public:
	CChangeLayerCommand(size_t position, bool isToUp, CCanvas* model);
	~CChangeLayerCommand();

	void Execute() override;
	void Unexecute() override;

private:
	size_t m_position;
	bool m_isToUp;
};

