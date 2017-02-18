#pragma once
#include "Toolbar.h"
#include "ActionButton.h"
#include "CanvasView.h"

class CMainView 
{
public:
	CMainView();
	~CMainView();

	std::shared_ptr<CParentLayer> const& GetRoot() const;
	std::shared_ptr<CCanvasView> const& GetCanvas() const;

	void SetDocDataState(bool isSaved);
	void SetCanvasSize(Vec2 const& size);

	void StartShow();

	signal::Connection DoOnShapeAdded(std::function<void(ShapeType, Vec2)> const& action);
	signal::Connection DoOnPictureAdded(std::function<void(Vec2, std::string)> const& action);
	signal::Connection DoOnDeleteShape(std::function<void(size_t)> const& action);
	signal::Connection DoOnRedo(std::function<void()> const& action);
	signal::Connection DoOnUndo(std::function<void()> const& action);
	signal::Connection DoOnSave(std::function<void(const std::string&)> const& action);
	signal::Connection DoOnOpen(std::function<void(const std::string&)> const& action);
	signal::Connection DoOnCreate(std::function<void()> const& action);
	signal::Connection DoOnChangeShapeRect(std::function<void(size_t, Vec2, Vec2)> const& action);
	signal::Connection DoOnChangeShapeLayer(std::function<void(size_t, bool)> const& action);

private:
	void OpenNewFile();
	bool SaveCurrentState();
	void CreateNewFile();
	bool SaveChangesDialog();

	void Redo();
	void Undo();

	void PrepareAddShapeSignal(ShapeType type);

	void CMainView::OnKeyPressed(sf::Event::KeyEvent const & event);

	void InitRootLayer();
	void InitCanvas();

	std::shared_ptr<CToolbar> CreateToolbar();
	std::shared_ptr<CActionButton> CreateButton(Vec2 const& size, SColor const& color, std::function<void()> const& function, std::string const& texturePath = std::string());
	
	std::shared_ptr<CParentLayer> m_root;
	std::shared_ptr<CCanvasView> m_canvas;

	bool m_dataWasChange = false;

	boost::signals2::signal<void(ShapeType, Vec2)> m_onShapeAdd;
	boost::signals2::signal<void(Vec2, std::string)> m_onPictureAdd;
	boost::signals2::signal<void(size_t)> m_onDeleteShape;
	boost::signals2::signal<void(size_t, bool)> m_onChangeShapeLayer;
	boost::signals2::signal<void(size_t, Vec2, Vec2)> m_onChangedRect;
	boost::signals2::signal<void()> m_onRedo;
	boost::signals2::signal<void()> m_onUndo;
	boost::signals2::signal<void(const std::string&)> m_onSave;
	boost::signals2::signal<void(const std::string&)> m_onOpen;
	boost::signals2::signal<void()> m_onCreate;

};

