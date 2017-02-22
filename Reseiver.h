#pragma once
#include <memory>

struct ICommand;

struct IHistory
{
	virtual void PushCommand(std::shared_ptr<ICommand> const& command) = 0;
	virtual void Redo() = 0;
	virtual void Undo() = 0;

	virtual void Clear() = 0;
	virtual ~IHistory() = default;
};