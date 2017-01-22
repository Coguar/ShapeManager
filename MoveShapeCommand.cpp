#include "stdafx.h"
#include "MoveShapeCommand.h"

CMoveShapeCommand::CMoveShapeCommand(std::shared_ptr<CShape> const & shape, Vec2 const & oldPos)
	: m_shape(shape)
	, m_oldPos(oldPos)
	, m_newPos(shape->GetPosition())
{}

CMoveShapeCommand::~CMoveShapeCommand()
{
}

void CMoveShapeCommand::Execute()
{
	m_shape->SetPosition(m_newPos);
}

void CMoveShapeCommand::Unexecute()
{
	m_shape->SetPosition(m_oldPos);
}
