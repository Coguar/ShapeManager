#include "stdafx.h"
#include "History.h"

CHistory::CHistory()
{
}


CHistory::~CHistory()
{
}

void CHistory::PushCommand(std::shared_ptr<ICommand> const & command)
{
	command->Execute();
	ClearOutdatedBranch();
	m_doneCommands.push_back(command);
	++m_currentCommandNumber;
}

void CHistory::Redo()
{
	if (m_doneCommands.size() != 0 && m_currentCommandNumber < m_doneCommands.size())
	{
		m_doneCommands[m_currentCommandNumber++]->Execute();
	}
}

void CHistory::Undo()
{
	if (m_currentCommandNumber > 0)
	{
		m_doneCommands[--m_currentCommandNumber]->Unexecute();
	}
}

void CHistory::Clear()
{
	m_currentCommandNumber = 0;
	m_doneCommands.clear();
}

void CHistory::ClearOutdatedBranch()
{
	m_doneCommands.erase(m_doneCommands.begin() + m_currentCommandNumber, m_doneCommands.end());
}
