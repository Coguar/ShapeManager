#pragma once
#include "CommandInterface.h"

class SModelShape;

class CChangeShapeRectCommand :
	public ICommand
{
public:
	CChangeShapeRectCommand(CBoundingRect const& newRect, CBoundingRect const& oldRect, std::shared_ptr<SModelShape> const& shapeModel);
	~CChangeShapeRectCommand();

	void Execute() override;
	void Unexecute() override;
	void Destroy() override;
private:
	CBoundingRect m_oldRect;
	CBoundingRect m_newRect;

	std::shared_ptr<SModelShape> m_model;
};

