#pragma once

class CHistory;

struct IHistoryManipulator
{

	virtual void RedoCommand() = 0;
	virtual void UndoCommand() = 0;
	virtual void ClearHistory() = 0;
	virtual CHistory* GetHistory() const = 0;
	virtual ~IHistoryManipulator() = default;
};