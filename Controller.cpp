#include "stdafx.h"
#include "Controller.h"


CController::CController()
{
	m_appModel = std::make_shared<CApplicationModel>();
	m_view = std::make_shared<CMainView>();

	ConnectSignalsFromModel();
	ConnectSignalsFromView();
}


CController::~CController()
{
}

void CController::Start()
{
	m_view->StartShow();
}

void CController::ConnectSignalsFromView()
{
	m_view->DoOnShapeAdded(boost::bind(&CApplicationModel::AddShape, m_appModel.get(), _1, _2));
	m_view->DoOnDeleteShape(boost::bind(&CApplicationModel::DeleteShape, m_appModel.get(), _1));
	m_view->DoOnRedo(boost::bind(&CApplicationModel::RedoCommand, m_appModel.get()));
	m_view->DoOnUndo(boost::bind(&CApplicationModel::UndoCommand, m_appModel.get()));
	m_view->DoOnOpen(boost::bind(&CApplicationModel::Open, m_appModel.get(), _1));
	m_view->DoOnSave(boost::bind(&CApplicationModel::Save, m_appModel.get(), _1));
	m_view->DoOnCreate(boost::bind(&CApplicationModel::Clear, m_appModel.get()));
	m_view->DoOnChangeShapeRect(boost::bind(&CApplicationModel::ChangeShapeRect, m_appModel.get(), _1, _2, _3));
}

void CController::ConnectSignalsFromModel()
{
	auto shapesCollection = m_appModel->GetShapesCollection();
	auto canvas = m_view->GetCanvas();

	shapesCollection->DoOnShapeAdd(boost::bind(&CCanvas::AddShape, canvas.get(), _1, _2));
	shapesCollection->DoOnShapeDelete(boost::bind(&CCanvas::DeleteShape, canvas.get(), _1));
	shapesCollection->DoOnShapesClear(boost::bind(&CCanvas::Clear, canvas.get()));
	shapesCollection->DoOnDataSaved(boost::bind(&CMainView::SetDocDataState, m_view.get(), true));
	shapesCollection->DoOndataChanged(boost::bind(&CMainView::SetDocDataState, m_view.get(), false));
}
