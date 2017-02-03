#include "stdafx.h"
#include "ApplicationModel.h"
#include "History.h"
#include "DeleteShapeCommand.h"
#include "ChangeBoundingRectCommand.h"
#include "AddShapeCommand.h"
#include "FileReader.h"

CApplicationModel::CApplicationModel()
{
	m_history = std::make_unique<CHistory>();
	m_domainModel = std::make_unique<CDomainModel>();
}


CApplicationModel::~CApplicationModel()
{
}

void CApplicationModel::AddShape(ShapeType type, Vec2 const& position)
{
	auto shape = std::make_shared<SModelShape>(type, position, INITIALIZATION_SHAPE_SIZE);
	m_history->PushCommand(std::make_shared<CAddShapeCommand>(shape, m_domainModel.get()));
}

void CApplicationModel::DeleteShape(size_t number)
{
	if (number != UINT_MAX)
	{
		m_history->PushCommand(std::make_shared<CDeleteShapeCommand>(number, m_domainModel.get()));
	}
}

void CApplicationModel::ChangeShapeRect(size_t number, Vec2 const & pos, Vec2 const & size)
{
	auto shape = m_domainModel->GetData()[number];
	auto oldRect = CBoundingRect(shape->GetPosition(), shape->GetSize());
	m_history->PushCommand(std::make_shared<CChangeBoundingRectCommand>(number, CBoundingRect(pos, size), oldRect, m_domainModel.get()));
}

void CApplicationModel::RedoCommand()
{
	m_history->Redo();
}

void CApplicationModel::UndoCommand()
{
	m_history->Undo();
}

void CApplicationModel::Save(std::string const & path)
{
	if (!path.empty())
	{
		CFileReader::Save(path, m_domainModel->GetData());
		m_domainModel->DataSaved();
	}
}

void CApplicationModel::Open(std::string const & path)
{
	if (!path.empty())
	{
		Clear();
		m_domainModel->SetNewShapeList(CFileReader::Open(path));
		m_domainModel->DataSaved();
	}
}

void CApplicationModel::Clear()
{
	m_history->Clear();
	m_domainModel->Clear();
}

CDomainModel * CApplicationModel::GetShapesCollection() const
{
	return m_domainModel.get();
}
