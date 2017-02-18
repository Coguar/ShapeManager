#include "stdafx.h"
#include "ApplicationModel.h"
#include "History.h"
#include "DeleteShapeCommand.h"
#include "AddShapeCommand.h"
#include "ChangeLayerCommand.h"
#include "FileReader.h"
#include "ShapePresenter.h"
#include "Picture.h"

using namespace signal;

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

void CApplicationModel::AddPicture(Vec2 const & position, std::string const & path)
{
	auto picture = std::make_shared<CPicture>(position, INITIALIZATION_SHAPE_SIZE);
	picture->SetTexturePath(path);
	m_history->PushCommand(std::make_shared<CAddShapeCommand>(picture, m_domainModel.get()));
}

void CApplicationModel::DeleteShape(size_t position)
{
	if (position != UINT_MAX)
	{
		m_history->PushCommand(std::make_shared<CDeleteShapeCommand>(position, m_domainModel.get()));
	}
}

void CApplicationModel::MoveShapeLayer(size_t position, bool isToUp)
{
	if (position != UINT_MAX)
	{
		m_history->PushCommand(std::make_shared<CChangeLayerCommand>(position, isToUp, m_domainModel.get()));
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

Vec2 CApplicationModel::GetCanvasSize() const
{
	return m_domainModel->GetSize();
}

Connection CApplicationModel::DoOnShapeAdded(std::function<void(std::shared_ptr<CShapePresenter>, size_t)> const & action)
{
	return m_onAddShape.connect(action);
}

Connection CApplicationModel::DoOnShapeDelete(std::function<void(size_t)> const & action)
{
	return m_domainModel->DoOnShapeDelete(action);
}

Connection CApplicationModel::DoOnShapesClear(std::function<void()> const & action)
{
	return m_domainModel->DoOnShapesClear(action);
}

Connection CApplicationModel::DoOnSavedStateChanged(std::function<void(bool)> const & action)
{
	return m_history->DoOnSavedStateChanged(action);
}

signal::Connection CApplicationModel::DoOnShapesLayerMove(std::function<void(size_t, bool)> const & action)
{
	return m_domainModel->DoOnShapesLayerMove(action);
}

void CApplicationModel::ShapeAdded(std::shared_ptr<SModelShape> const & shape, size_t position)
{
	auto presenter = std::make_shared<CShapePresenter>(shape);
	presenter->SetHistory(m_history.get());

	m_onAddShape(presenter, position);
}
