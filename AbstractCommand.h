#pragma once
#include "CommandInterface.h"

class CAbstractCommand :
	public ICommand
{
public:
	CAbstractCommand();
	~CAbstractCommand();
	bool IsDone() const override;

protected:
	void SetDoneState(bool isDone);
	bool m_isDone = false;
};

