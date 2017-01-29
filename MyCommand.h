#pragma once
#include "CommandInterface.h"
#include "DomainModel.h"
class CMyCommand :
	public ICommand
{
public:
	CMyCommand(CDomainModel* model);
	~CMyCommand();
protected:
	CDomainModel * m_model = nullptr;
};

