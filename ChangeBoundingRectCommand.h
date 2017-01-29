#pragma once
#include "MyCommand.h"

class CChangeBoundingRectCommand :
	public CMyCommand
{
public:
	CChangeBoundingRectCommand(size_t position, CBoundingRect const& newRect, CBoundingRect const& oldRect, CDomainModel* model);
	~CChangeBoundingRectCommand();

	void Execute() override;
	void Unexecute() override;
private:
	CBoundingRect m_oldRect;
	CBoundingRect m_newRect;
	size_t m_shapePosition = 0;
};

