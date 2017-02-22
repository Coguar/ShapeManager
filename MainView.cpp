#include "stdafx.h"
#include "FileReader.h"
#include "DialogManager.h"
#include "TextureCache.h"
#include "ShapeModel.h"
#include "MainView.h"

CMainView::CMainView()
{
	InitRootLayer();
}


CMainView::~CMainView()
{
}

std::shared_ptr<CParentLayer> const & CMainView::GetRoot() const
{
	return m_root;
}

std::shared_ptr<CCanvasView> const & CMainView::GetCanvas() const
{
	return m_canvas;
}

void CMainView::SetDocDataState(bool isSaved)
{
	m_dataWasChange = !isSaved;
}

void CMainView::SetCanvasSize(Vec2 const & size)
{
	m_canvas->SetSize(size);
}


void CMainView::OpenNewFile()
{
	if (SaveChangesDialog())
	{
		auto path = CDialogManager::GetFileToOpen();
		if (!path.empty())
		{
			m_onOpen(path);
		}
	}
}

bool CMainView::SaveCurrentState()
{
	auto path = CDialogManager::GetFileToSave();
	if (!path.empty())
	{
		m_onSave(path);
		return true;
	}
	return false;
}

void CMainView::CreateNewFile()
{
	if (SaveChangesDialog())
	{
		m_onCreate();
	}
}

bool CMainView::SaveChangesDialog()
{
	if (!m_dataWasChange)
	{
		return true;
	}
	switch (CDialogManager::StartDialog(SAVE_MSG))
	{
	case DialogAnswer::Yes:
		return SaveCurrentState();
	case DialogAnswer::No:
		return true;
	case DialogAnswer::Cancel:
		return false;
	}
	return false;
}

void CMainView::Redo()
{
	m_onRedo();
}

void CMainView::Undo()
{
	m_onUndo();
}

void CMainView::PrepareAddShapeSignal(ShapeType type)
{
	auto canvasSize = m_canvas->GetSize();
	auto canvasPos = m_canvas->GetPosition();
	Vec2 position = { canvasPos.x + canvasSize.x / 2.0, canvasPos.y + canvasSize.y / 2.0 };

	if (type == ShapeType::Picture)
	{
		auto path = CDialogManager::GetPathToPicture();
		if(!path.empty())
			m_onPictureAdd(position, path);
	}
	else
	{
		m_onShapeAdd(type, position);
	}
}

void CMainView::InitRootLayer()
{
	m_root = std::make_shared<CParentLayer>(MAIN_WINDOW_SIZE);
	InitCanvas();

	auto toolbar = CreateToolbar();
	m_root->AddChild(toolbar);

	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&CMainView::PrepareAddShapeSignal, this, ShapeType::Circle), CIRCLE_PATH));
	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&CMainView::PrepareAddShapeSignal, this, ShapeType::Rectangle), RECTANGLE_PATH));
	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&CMainView::PrepareAddShapeSignal, this, ShapeType::Triangle), TRIANGLE_PATH));
	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&CMainView::PrepareAddShapeSignal, this, ShapeType::Picture), PICTURE_PATH));


	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&CMainView::Undo, this), UNDO_PATH));
	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&CMainView::Redo, this), REDO_PATH));

	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&CMainView::OpenNewFile, this), OPEN_PATH));
	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&CMainView::SaveCurrentState, this), SAVE_PATH));
	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&CMainView::CreateNewFile, this), NEW_PATH));
	
	m_root->AddChild(m_canvas);
}

void CMainView::InitCanvas()
{
	m_canvas = std::make_shared<CCanvasView>();
	m_canvas->SetPosition(CANVAS_POSITION);
	m_canvas->SetSize(CANVAS_SIZE);
	m_canvas->SetColor(color::WHITE);
}

void CMainView::StartShow()
{
	CTextureCache cache;

	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTI_ALIASING_LVL;
	sf::RenderWindow window(sf::VideoMode(unsigned int(MAIN_WINDOW_SIZE.x), unsigned int(MAIN_WINDOW_SIZE.y)), TITLE, sf::Style::Close, settings);
	window.setFramerateLimit(FPS);

	sf::Image icon;
	icon.loadFromFile(ICON_PATH);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				if(SaveChangesDialog())
					window.close();
				break;
			case sf::Event::KeyPressed:
				OnKeyPressed(event.key);
				break;
			default:
				m_root->DispatchEvent(event);
				break;
			}
		}
		window.clear();
		m_root->Draw(&window, &cache);
		window.display();
	}
}

signal::Connection CMainView::DoOnShapeAdded(std::function<void(ShapeType, Vec2)> const & action)
{
	return m_onShapeAdd.connect(action);
}

signal::Connection CMainView::DoOnPictureAdded(std::function<void(Vec2, std::string)> const & action)
{
	return m_onPictureAdd.connect(action);
}

signal::Connection CMainView::DoOnDeleteShape(std::function<void(size_t)> const & action)
{
	return m_onDeleteShape.connect(action);
}

signal::Connection CMainView::DoOnRedo(std::function<void()> const & action)
{
	return m_onRedo.connect(action);
}

signal::Connection CMainView::DoOnUndo(std::function<void()> const & action)
{
	return m_onUndo.connect(action);
}

signal::Connection CMainView::DoOnSave(std::function<void(const std::string&)> const & action)
{
	return m_onSave.connect(action);
}

signal::Connection CMainView::DoOnOpen(std::function<void(const std::string&)> const & action)
{
	return m_onOpen.connect(action);
}

signal::Connection CMainView::DoOnCreate(std::function<void()> const & action)
{
	return m_onCreate.connect(action);
}

signal::Connection CMainView::DoOnChangeShapeRect(std::function<void(size_t, Vec2, Vec2)> const & action)
{
	return m_onChangedRect.connect(action);
}

signal::Connection CMainView::DoOnChangeShapeLayer(std::function<void(size_t, bool)> const & action)
{
	return m_onChangeShapeLayer.connect(action);
}

std::shared_ptr<CToolbar> CMainView::CreateToolbar()
{
	auto toolbar = std::make_shared<CToolbar>();
	toolbar->SetPosition(TOOLBAR_POSITION);
	toolbar->SetSize(TOOLBAR_SIZE);
	toolbar->SetColor(color::TOOLBAR_COLOR);
	return toolbar;
}

std::shared_ptr<CActionButton> CMainView::CreateButton(Vec2 const & size, SColor const & color, std::function<void()> const & function, std::string const & texturePath)
{
	auto btn = std::make_shared<CActionButton>(color);
	btn->SetSize(size);
	btn->SetTexturePath(texturePath);
	btn->SetAction(function);
	btn->SetActiveColor(color::LITE_GRAY);
	return btn;
}

void CMainView::OnKeyPressed(sf::Event::KeyEvent const & event)
{
	switch (event.code)
	{
	case sf::Keyboard::Delete:
		m_onDeleteShape(m_canvas->GetSelectedShapeNum());
		break;
	case sf::Keyboard::Up:
		m_onChangeShapeLayer(m_canvas->GetSelectedShapeNum(), true);
		break;
	case sf::Keyboard::Down:
		m_onChangeShapeLayer(m_canvas->GetSelectedShapeNum(), false);
	default:
		break;
	}
}