#pragma once
#include <memory>

struct IHistory
{
	virtual void Redo() = 0;
	virtual void Undo() = 0;

	virtual void Clear() = 0;
	virtual ~IHistory() = default;
};