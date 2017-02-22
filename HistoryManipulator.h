#pragma once

struct IHistory;

struct IHistoryManipulator
{

	virtual void RedoCommand() = 0;
	virtual void UndoCommand() = 0;
	virtual void ClearHistory() = 0;
	virtual IHistory* GetHistory() const = 0;
	virtual ~IHistoryManipulator() = default;
};