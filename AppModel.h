#pragma once
#include "SceneView.h"
#include "Toolbar.h"
#include "ActionButton.h"
#include "Canvas.h"

struct IReseiver;

class CAppModel
{
public:
	CAppModel();
	~CAppModel();

	std::shared_ptr<CParentLayer> const& GetRoot() const;
	std::shared_ptr<CCanvas> const& GetCanvas() const;

	std::shared_ptr<IReseiver> const& GetReseiver() const;
	void DeleteSelectedShape();
private:
	void RootInit();
	void CanvasInit();
	std::shared_ptr<CToolbar> CreateToolbar();
	std::shared_ptr<CActionButton> CreateButton(Vec2 const& size, SColor const& color, std::function<void()> const& function, std::string const& texturePath = std::string());
	
	std::shared_ptr<CParentLayer> m_root;
	std::shared_ptr<CCanvas> m_canvas;
	std::shared_ptr<IReseiver> m_history;
};

