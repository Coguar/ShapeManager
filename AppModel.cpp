#include "stdafx.h"
#include "AppModel.h"
#include "History.h"

CAppModel::CAppModel()
{
	InitRootLayer();
}


CAppModel::~CAppModel()
{
}

std::shared_ptr<CParentLayer> const & CAppModel::GetRoot() const
{
	return m_root;
}

std::shared_ptr<CCanvas> const & CAppModel::GetCanvas() const
{
	return m_canvas;
}

std::shared_ptr<IReseiver> const & CAppModel::GetReseiver() const
{
	return m_history;
}

void CAppModel::DeleteSelectedShape()
{
	m_canvas->DeleteSelectedShape();
}

void CAppModel::InitRootLayer()
{
	m_root = std::make_shared<CParentLayer>(MAIN_WINDOW_SIZE);
	InitCanvas();
	m_history = std::make_shared<CHistory>(m_canvas);
	m_canvas->SetReseiver(m_history);
	m_canvas->GetFSelectFrame()->SetReseiver(m_history);
	auto toolbar = CreateToolbar();
	m_root->AddChild(toolbar);
	auto foo = [](CCanvas * canvas, ShapeType type) {canvas->CreateShape(type); };

	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(foo, m_canvas.get(), ShapeType::Circle), CIRCLE_PATH));
	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(foo, m_canvas.get(), ShapeType::Rectangle), RECTANGLE_PATH));
	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(foo, m_canvas.get(), ShapeType::Triangle), TRIANGLE_PATH));

	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&IReseiver::Undo, m_history), UNDO_PATH));
	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&IReseiver::Redo, m_history), REDO_PATH));
	m_root->AddChild(m_canvas);
}

void CAppModel::InitCanvas()
{
	m_canvas = std::make_shared<CCanvas>();
	m_canvas->SetPosition(CANVAS_POSITION);
	m_canvas->SetSize(CANVAS_SIZE);
	m_canvas->SetColor(color::WHITE);
}

std::shared_ptr<CToolbar> CAppModel::CreateToolbar()
{
	auto toolbar = std::make_shared<CToolbar>();
	toolbar->SetPosition(TOOLBAR_POSITION);
	toolbar->SetSize(TOOLBAR_SIZE);
	toolbar->SetColor(color::YELLOW);
	return toolbar;
}

std::shared_ptr<CActionButton> CAppModel::CreateButton(Vec2 const & size, SColor const & color, std::function<void()> const & function, std::string const & texturePath)
{
	auto btn = std::make_shared<CActionButton>(color);
	btn->SetSize(size);
	btn->SetTexturePath(texturePath);
	btn->SetAction(function);
	btn->SetActiveColor(color::LITE_GRAY);
	return btn;
}
