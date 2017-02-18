#include "stdafx.h"
#include "MainView.h"
#include "ApplicationModel.h"
#include "Controller.h"

CController::CController()
{
	m_manager = std::make_unique<CFileManager>();
}


CController::~CController()
{
}

void CController::SetModelManipulator(ICollectionShapesManipulator * manipulator)
{
	m_manipulator = manipulator;
	SetConnections();
}

void CController::SetSignalsConnector(IModelSignalsConnector * connector)
{
	m_connector = connector;
	SetConnections();
}

void CController::SetView(std::shared_ptr<CMainView> const & view)
{
	m_view = view;
	SetConnections();
}

void CController::Start()
{
	m_view->StartShow();
}

void CController::SetConnections()
{
	if (m_view && m_manipulator)
	{
		ConnectSignalsFromView();
		m_view->SetCanvasSize(m_manipulator->GetCanvasSize());
	}
	if (m_view && m_connector)
	{
		ConnectSignalsFromModel();
	}
}

void CController::ConnectSignalsFromView()
{
	m_connections += m_view->DoOnShapeAdded(boost::bind(&ICollectionShapesManipulator::AddShape, m_manipulator, _1, _2));
	m_connections += m_view->DoOnPictureAdded(boost::bind(&CController::AddPicture, this, _1, _2));
	m_connections += m_view->DoOnDeleteShape(boost::bind(&ICollectionShapesManipulator::DeleteShape, m_manipulator,_1));
	m_connections += m_view->DoOnRedo(boost::bind(&ICollectionShapesManipulator::RedoCommand, m_manipulator));
	m_connections += m_view->DoOnUndo(boost::bind(&ICollectionShapesManipulator::UndoCommand, m_manipulator));
	m_connections += m_view->DoOnOpen(boost::bind(&ICollectionShapesManipulator::Open, m_manipulator, _1));
	m_connections += m_view->DoOnSave(boost::bind(&ICollectionShapesManipulator::Save, m_manipulator, _1));
	m_connections += m_view->DoOnCreate(boost::bind(&ICollectionShapesManipulator::Clear, m_manipulator));
	m_connections += m_view->DoOnChangeShapeLayer(boost::bind(&ICollectionShapesManipulator::MoveShapeLayer, m_manipulator, _1, _2));
}

void CController::ConnectSignalsFromModel()
{
	auto canvas = m_view->GetCanvas();

	m_connections += m_connector->DoOnShapeAdded(boost::bind(&CCanvasView::AddShape, canvas.get(), _1, _2));
	m_connections += m_connector->DoOnShapeDelete(boost::bind(&CCanvasView::DeleteShape, canvas.get(), _1));
	m_connections += m_connector->DoOnShapesClear(boost::bind(&CCanvasView::Clear, canvas.get()));
	m_connections += m_connector->DoOnSavedStateChanged(boost::bind(&CMainView::SetDocDataState, m_view.get(), _1));
	m_connections += m_connector->DoOnShapesLayerMove(boost::bind(&CCanvasView::MoveShapeLayer, canvas.get(), _1, _2));
}

void CController::AddPicture(Vec2 const & position, std::string const & path)
{
	m_manipulator->AddPicture(position, m_manager->AddFile(path));
}
