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

	signal::Connection DoOnSavedStateChanged(std::function<void(bool)> const& action);

	void RememberCurrentState();

private:
	void SendDataStateSignal();
	void ClearOutdatedBranch();

	void DecreaseCommandNumber();
	void IncreaseCommandNumber();

	std::vector<std::shared_ptr<ICommand>> m_doneCommands;
	size_t m_currentCommandNumber = 0;

	boost::signals2::signal<void(bool)> m_onSavedStateChanged;
	std::shared_ptr<ICommand> m_lastSavedState;
};

