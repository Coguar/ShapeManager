#pragma once
#include "CommandInterface.h"
#include "Canvas.h"

class CMyCommand :
	public ICommand
{
public:
	CMyCommand();
	~CMyCommand();
	void SetCanvas(std::shared_ptr<CCanvas> const& canvas);
protected:
	std::shared_ptr<CCanvas> m_canvas;
};

