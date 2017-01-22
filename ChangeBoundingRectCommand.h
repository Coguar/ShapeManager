#pragma once
#include "MyCommand.h"

class CChangeBoundingRectCommand :
	public CMyCommand
{
public:
	CChangeBoundingRectCommand(std::shared_ptr<CShape> const& shape, CBoundingRect const& oldRect);
	~CChangeBoundingRectCommand();

	void Execute() override;
	void Unexecute() override;
private:
	CBoundingRect m_oldRect;
	CBoundingRect m_newRect;
	std::shared_ptr<CShape> m_shape;
};

