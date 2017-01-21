#include "stdafx.h"
#include "AppModel.h"


CAppModel::CAppModel()
{
	RootInit();
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

void CAppModel::RootInit()
{
	m_root = std::make_shared<CParentLayer>(Vec2( 800, 600 ));
	CanvasInit();
	auto toolbar = CreateToolbar();
	m_root->AddChild(toolbar);
	auto foo = [](CCanvas * canvas, ShapeType type) {canvas->CreateShape(type); };

	toolbar->AddChild(CreateButton({ 80.0, 80.0 }, color::WHITE, std::bind(foo, m_canvas.get(), ShapeType::Circle), std::string("./res/circle.png")));
	toolbar->AddChild(CreateButton({ 80.0, 80.0 }, color::WHITE, std::bind(foo, m_canvas.get(), ShapeType::Rectangle), std::string("./res/square.png")));
	toolbar->AddChild(CreateButton({ 80.0, 80.0 }, color::WHITE, std::bind(foo, m_canvas.get(), ShapeType::Triangle), std::string("./res/triangle.png")));

	m_root->AddChild(m_canvas);

}

void CAppModel::CanvasInit()
{
	m_canvas = std::make_shared<CCanvas>();
	m_canvas->SetPosition({ 5, 105 });
	m_canvas->SetSize({ 790, 490 });
	m_canvas->SetColor(SColor(255, 255, 255, 255));
}

std::shared_ptr<CToolbar> CAppModel::CreateToolbar()
{
	auto toolbar = std::make_shared<CToolbar>();
	toolbar->SetPosition({ 0, 0 });
	toolbar->SetSize({ 800, 100 });
	toolbar->SetColor(SColor(255, 255, 0, 255));
	return toolbar;
}

std::shared_ptr<CActionButton> CAppModel::CreateButton(Vec2 const & size, SColor const & color, std::function<void()> const & function, std::string const & texturePath)
{
	auto btn = std::make_shared<CActionButton>();
	btn->SetSize(size);
	btn->SetColor(color);
	btn->SetTexturePath(texturePath);
	btn->SetAction(function);
	return btn;
}
