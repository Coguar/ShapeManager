#include "stdafx.h"
#include "ApplicationModel.h"
#include "History.h"
#include "DeleteShapeCommand.h"
#include "AddShapeCommand.h"
#include "FileReader.h"
#include "ShapePresenter.h"

CApplicationModel::CApplicationModel()
{
	m_history = std::make_unique<CHistory>();
	m_domainModel = std::make_unique<CCanvas>();
	m_domainModel->DoOnShapeAdd(boost::bind(&CApplicationModel::ShapeAdded, this, _1, _2));
}


CApplicationModel::~CApplicationModel()
{
}

void CApplicationModel::AddShape(ShapeType type, Vec2 const& position)
{
	auto shape = std::make_shared<SModelShape>(type, position, INITIALIZATION_SHAPE_SIZE);
	m_history->PushCommand(std::make_shared<CAddShapeCommand>(shape, m_domainModel.get()));
}

void CApplicationModel::DeleteShape(size_t position)
{
	if (position != UINT_MAX)
	{
		m_history->PushCommand(std::make_shared<CDeleteShapeCommand>(position, m_domainModel.get()));
	}
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
		m_history->RememberCurrentState();
	}
}

void CApplicationModel::Open(std::string const & path)
{
	if (!path.empty())
	{
		Clear();
		m_domainModel->SetNewShapeList(CFileReader::Open(path));
	}
}

void CApplicationModel::Clear()
{
	m_history->Clear();
	m_domainModel->Clear();
}

void CApplicationModel::SetCanvasSize(Vec2 const & size)
{
	m_domainModel->SetSize(size);
}

Vec2 CApplicationModel::GetCanvasSize() const
{
	return m_domainModel->GetSize();
}

void CApplicationModel::DoOnShapeAdded(std::function<void(std::shared_ptr<CShapePresenter>, size_t)> const & action)
{
	m_onAddShape.connect(action);
}

void CApplicationModel::DoOnShapeDelete(std::function<void(size_t)> const & action)
{
	m_domainModel->DoOnShapeDelete(action);
}

void CApplicationModel::DoOnShapesClear(std::function<void()> const & action)
{
	m_domainModel->DoOnShapesClear(action);
}

void CApplicationModel::DoOnSavedStateChanged(std::function<void(bool)> const & action)
{
	m_history->DoOnSavedStateChanged(action);
}

void CApplicationModel::ShapeAdded(std::shared_ptr<SModelShape> const & shape, size_t position)
{
	auto presenter = std::make_shared<CShapePresenter>(shape);
	presenter->SetHistory(m_history.get());

	m_onAddShape(presenter, position);
}
