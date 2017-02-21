#pragma once
#include "AbstractCommand.h"

class SModelShape;

class CChangeShapeRectCommand :
	public CAbstractCommand
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

