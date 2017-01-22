#include "stdafx.h"
#include "History.h"
#include "AddShapeCommand.h"
#include "ChangeBoundingRectCommand.h"
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
}

void CHistory::MoveShape(ShapePtr const & shape, Vec2 const & newPos)
{
}

void CHistory::ResizeShape(ShapePtr const & shape, Vec2 const & oldSize)
{
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

void CHistory::ClearOutdatedBranch()
{
	m_doneCommands.erase(m_doneCommands.begin() + m_currentCommandNumber, m_doneCommands.end());
}
