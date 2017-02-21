#include "stdafx.h"
#include "AbstractCommand.h"


CAbstractCommand::CAbstractCommand()
{
}


CAbstractCommand::~CAbstractCommand()
{
}

bool CAbstractCommand::IsDone() const
{
	return m_isDone;
}

void CAbstractCommand::SetDoneState(bool isDone)
{
	m_isDone = isDone;
}
