#pragma once
#include "Reseiver.h"
#include "CommandInterface.h"


class CHistory :
	public IHistory
{
public:
	CHistory();
	~CHistory();

	void PushCommand(std::shared_ptr<ICommand> const& command);

	void Redo() override;
	void Undo() override;

	void Clear() override;

private:
	void ClearOutdatedBranch();

	std::vector<std::shared_ptr<ICommand>> m_doneCommands;
	size_t m_currentCommandNumber = 0;
};

