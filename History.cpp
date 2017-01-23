#include "stdafx.h"
#include "AddShapeCommand.h"
#include "ChangeBoundingRectCommand.h"
#include "DeleteShapeCommand.h"
#include "Canvas.h"
#include "History.h"

CHistory::CHistory(std::shared_ptr<CCanvas> const& canvas)
	: m_canvas(canvas)
{
}


CHistory::~CHistory()
{
}

void CHistory::AddShape(ShapePtr const & shape)
{
	auto command = std::make_shared<CAddShapeCommand>(shape);
	command->SetCanvas(m_canvas);
	command->Execute();
	ClearOutdatedBranch();
	m_doneCommands.push_back(command);
	++m_currentCommandNumber;
}

void CHistory::DeleteShape(ShapePtr const & shape, int num)
{
	auto command = std::make_shared<CDeleteShapeCommand>(shape, num);
	command->SetCanvas(m_canvas);
	command->Execute();
	ClearOutdatedBranch();
	m_doneCommands.push_back(command);
	++m_currentCommandNumber;
}

void CHistory::ChangeRect(ShapePtr const & shape, CBoundingRect const & rect)
{
	auto command = std::make_shared<CChangeBoundingRectCommand>(shape, rect);
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
