#include "stdafx.h"
#include "Controller.h"


CController::CController()
{
	m_appModel = std::make_shared<CApplicationModel>();
	m_view = std::make_shared<CMainView>();

	m_view->SetCanvasSize(m_appModel->GetCanvasSize());

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
}

void CController::ConnectSignalsFromModel()
{
	auto canvas = m_view->GetCanvas();

	m_appModel->DoOnShapeAdded(boost::bind(&CCanvasView::AddShape, canvas.get(), _1, _2));
	m_appModel->DoOnShapeDelete(boost::bind(&CCanvasView::DeleteShape, canvas.get(), _1));
	m_appModel->DoOnShapesClear(boost::bind(&CCanvasView::Clear, canvas.get()));
	m_appModel->DoOnSavedStateChanged(boost::bind(&CMainView::SetDocDataState, m_view.get(), _1));
}
