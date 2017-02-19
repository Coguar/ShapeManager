#pragma once

#include "ConnectionsStorage.h"
#include "FileManager.h"

struct ICollectionShapesManipulator;
struct IDocumentManipulator;
struct IHistoryManipulator;
class CMainView;

class CController
{
public:
	CController();
	~CController();

	void SetModelManipulator(ICollectionShapesManipulator * collectionShapeManipulator);
	void SetHistoryManipulator(IHistoryManipulator * hystorymanipulator);
	void SetDocumentManipulator(IDocumentManipulator * documentManipulator);
	void SetView(std::shared_ptr<CMainView> const& view);

	void Start();
private:
	void SetConnections();

	void ConnectSignalsForDocument();
	void ConnectSignalsForView();
	void ConnectSignalsForHistory();
	void ConnectSignalsForShapeCollection();

	void AddPicture(Vec2 const & position, std::string const & path);

	ICollectionShapesManipulator * m_collectionShapeManipulator = nullptr;
	IHistoryManipulator * m_hystorymanipulator = nullptr;
	IDocumentManipulator * m_documentManipulator = nullptr;
	std::shared_ptr<CMainView> m_view;

	ScopedConnectionsStorage m_connections;
	std::unique_ptr<CFileManager> m_manager;
};

