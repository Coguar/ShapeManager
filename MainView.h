#pragma once
#include "Toolbar.h"
#include "ActionButton.h"
#include "Canvas.h"
#include "Observer.h"

class CMainView 
	: public CObservable<SEvent>
{
public:
	CMainView();
	~CMainView();

	std::shared_ptr<CParentLayer> const& GetRoot() const;
	std::shared_ptr<CCanvas> const& GetCanvas() const;

	void SetNewShapeList(std::vector<std::shared_ptr<SModelShape>> const& shapes);

	void SetEvent(EventType type);
	void SetDocDataState(bool isSaved);

	void StartShow();

protected:
	SEvent GetChangedData()const override;

private:
	void OpenNewFile();
	bool SaveCurrentState();
	void CreateNewFile();
	bool SaveChangesDialog();

	void CMainView::OnKeyPressed(sf::Event::KeyEvent const & event);

	void InitRootLayer();
	void InitCanvas();

	void CheckEvent();

	std::shared_ptr<CToolbar> CreateToolbar();
	std::shared_ptr<CActionButton> CreateButton(Vec2 const& size, SColor const& color, std::function<void()> const& function, std::string const& texturePath = std::string());
	
	std::shared_ptr<CParentLayer> m_root;
	std::shared_ptr<CCanvas> m_canvas;

	SEvent m_event;
	bool m_dataWasChange = false;
};

