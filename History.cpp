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
	IncreaseCommandNumber();
	SendDataStateSignal();
}

void CHistory::Redo()
{
	if (!m_doneCommands.empty())
	{
		IncreaseCommandNumber();
		m_doneCommands[m_currentCommandNumber]->Execute();
		SendDataStateSignal();
	}
}

void CHistory::Undo()
{
	if (!m_doneCommands.empty())
	{
		m_doneCommands[m_currentCommandNumber]->Unexecute();
		DecreaseCommandNumber();
		SendDataStateSignal();
	}
}

void CHistory::Clear()
{
	for (auto &command : m_doneCommands)
	{
		command->Destroy();
	}
	m_currentCommandNumber = 0;
	m_doneCommands.clear();
	RememberCurrentState();
	SendDataStateSignal();
}

signal::Connection CHistory::DoOnSavedStateChanged(std::function<void(bool)> const & action)
{
	return m_onSavedStateChanged.connect(action);
}


void CHistory::RememberCurrentState()
{
	if (!m_doneCommands.empty() && m_doneCommands[m_currentCommandNumber]->IsDone())
	{
			m_lastSavedState = m_doneCommands[m_currentCommandNumber];
	}
	else
	{
		m_lastSavedState.reset();
	}
	SendDataStateSignal();
}

void CHistory::SendDataStateSignal()
{
	if (m_doneCommands.empty() || m_lastSavedState == m_doneCommands[m_currentCommandNumber])
	{
		m_onSavedStateChanged(true);
	}
	else
	{
		m_onSavedStateChanged(false);
	}
}

void CHistory::ClearOutdatedBranch()
{
	if (m_doneCommands.empty())
		return;
	for (size_t i = m_currentCommandNumber; i < m_doneCommands.size(); ++i)
	{
		if (!m_doneCommands[i]->IsDone())
		{
			m_doneCommands[i]->Destroy();
		}
	}
	m_doneCommands.erase(m_doneCommands.begin() + m_currentCommandNumber + 1, m_doneCommands.end());
}

void CHistory::DecreaseCommandNumber()
{
	m_currentCommandNumber = m_currentCommandNumber == 0 ? 0 : m_currentCommandNumber - 1;
}

void CHistory::IncreaseCommandNumber()
{
	m_currentCommandNumber = m_currentCommandNumber == m_doneCommands.size() - 1 ? m_currentCommandNumber : m_currentCommandNumber + 1;
}
