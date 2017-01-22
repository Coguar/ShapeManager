#include "stdafx.h"
#include "MyCommand.h"


CMyCommand::CMyCommand()
{
}


CMyCommand::~CMyCommand()
{
}


void CMyCommand::SetCanvas(std::shared_ptr<CCanvas> const & canvas)
{
	m_canvas = canvas;
}
