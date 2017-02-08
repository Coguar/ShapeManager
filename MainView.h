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

	void DoOnShapeAdded(std::function<void(ShapeType, Vec2)> const& action);
	void DoOnDeleteShape(std::function<void(size_t)> const& action);
	void DoOnRedo(std::function<void()> const& action);
	void DoOnUndo(std::function<void()> const& action);
	void DoOnSave(std::function<void(const std::string&)> const& action);
	void DoOnOpen(std::function<void(const std::string&)> const& action);
	void DoOnCreate(std::function<void()> const& action);
	void DoOnChangeShapeRect(std::function<void(size_t, Vec2, Vec2)> const& action);

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
	boost::signals2::signal<void(size_t)> m_onDeleteShape;
	boost::signals2::signal<void(size_t, Vec2, Vec2)> m_onChangedRect;
	boost::signals2::signal<void()> m_onRedo;
	boost::signals2::signal<void()> m_onUndo;
	boost::signals2::signal<void(const std::string&)> m_onSave;
	boost::signals2::signal<void(const std::string&)> m_onOpen;
	boost::signals2::signal<void()> m_onCreate;

};

