#pragma once

#include "ConnectionsStorage.h"
#include "FileManager.h"

struct ICollectionShapesManipulator;
struct IModelSignalsConnector;
class CMainView;

class CController
{
public:
	CController();
	~CController();

	void SetModelManipulator(ICollectionShapesManipulator * manipulator);
	void SetSignalsConnector(IModelSignalsConnector * connector);
	void SetView(std::shared_ptr<CMainView> const& view);

	void Start();
private:
	void SetConnections();

	void ConnectSignalsFromView();
	void ConnectSignalsFromModel();

	void AddPicture(Vec2 const & position, std::string const & path);

	ICollectionShapesManipulator * m_manipulator;
	IModelSignalsConnector * m_connector;
	std::shared_ptr<CMainView> m_view;

	ScopedConnectionsStorage m_connections;
	std::unique_ptr<CFileManager> m_manager;
};

