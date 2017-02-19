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

void CController::SetModelManipulator(ICollectionShapesManipulator * collectionShapeManipulator)
{
	m_collectionShapeManipulator = collectionShapeManipulator;
	SetConnections();
}

void CController::SetHistoryManipulator(IHistoryManipulator * hystorymanipulator)
{
	m_hystorymanipulator = hystorymanipulator;
	m_shapePreesenterCreator = CShapePresenterCreator(m_hystorymanipulator->GetHistory());
	SetConnections();
}

void CController::SetDocumentManipulator(IDocumentManipulator * documentManipulator)
{
	m_documentManipulator = documentManipulator;
	SetConnections();
}

void CController::SetView(std::shared_ptr<CMainView> const & view)
{
	m_view = view;
	SetConnections();
}

void CController::CreateShapePresenter(std::shared_ptr<SModelShape> const & model, size_t position)
{
	m_onShapeAdded(m_shapePreesenterCreator.CreatePresenter(model), position);
}

void CController::Start()
{
	m_view->StartShow();
}

void CController::SetConnections()
{
	ConnectSignalsForDocument();
	ConnectSignalsForView();
	ConnectSignalsForHistory();
	ConnectSignalsForShapeCollection();
}

void CController::ConnectSignalsForDocument()
{
	if (m_view && m_documentManipulator)
	{
		m_connections += m_view->DoOnOpen(boost::bind(&IDocumentManipulator::Open, m_documentManipulator, _1, m_manager->GetTempFolderPath()));
		m_connections += m_view->DoOnSave(boost::bind(&IDocumentManipulator::Save, m_documentManipulator, _1));
	}
}

void CController::ConnectSignalsForView()
{
	if (m_view && m_collectionShapeManipulator)
	{
		auto canvas = m_view->GetCanvas();

		m_connections += m_collectionShapeManipulator->DoOnShapeAdded(boost::bind(&CController::CreateShapePresenter, this, _1, _2));
		m_connections += m_onShapeAdded.connect(boost::bind(&CCanvasView::AddShape, canvas.get(), _1, _2));
		m_connections += m_collectionShapeManipulator->DoOnShapeDelete(boost::bind(&CCanvasView::DeleteShape, canvas.get(), _1));
		m_connections += m_collectionShapeManipulator->DoOnShapesClear(boost::bind(&CCanvasView::Clear, canvas.get()));
		m_connections += m_collectionShapeManipulator->DoOnSavedStateChanged(boost::bind(&CMainView::SetDocDataState, m_view.get(), _1));
		m_connections += m_collectionShapeManipulator->DoOnShapesLayerMove(boost::bind(&CCanvasView::MoveShapeLayer, canvas.get(), _1, _2));
		m_connections += m_collectionShapeManipulator->DoOnResourceBecomingUnusable(&CFileManager::RemoveFile);
	}
}

void CController::ConnectSignalsForHistory()
{
	if (m_view && m_hystorymanipulator)
	{
		m_connections += m_view->DoOnRedo(boost::bind(&IHistoryManipulator::RedoCommand, m_hystorymanipulator));
		m_connections += m_view->DoOnUndo(boost::bind(&IHistoryManipulator::UndoCommand, m_hystorymanipulator));
		m_connections += m_view->DoOnCreate(boost::bind(&IHistoryManipulator::ClearHistory, m_hystorymanipulator));
	}
}

void CController::ConnectSignalsForShapeCollection()
{
	if (m_view && m_collectionShapeManipulator)
	{
		m_connections += m_view->DoOnShapeAdded(boost::bind(&ICollectionShapesManipulator::AddShape, m_collectionShapeManipulator, _1, _2));
		m_connections += m_view->DoOnPictureAdded(boost::bind(&CController::AddPicture, this, _1, _2));
		m_connections += m_view->DoOnDeleteShape(boost::bind(&ICollectionShapesManipulator::DeleteShape, m_collectionShapeManipulator, _1));
		m_connections += m_view->DoOnCreate(boost::bind(&ICollectionShapesManipulator::Clear, m_collectionShapeManipulator));
		m_connections += m_view->DoOnChangeShapeLayer(boost::bind(&ICollectionShapesManipulator::MoveShapeLayer, m_collectionShapeManipulator, _1, _2));
	}
}

void CController::AddPicture(Vec2 const & position, std::string const & path)
{
	m_collectionShapeManipulator->AddPicture(position, m_manager->AddFile(path));
}
