#include "stdafx.h"
#include "FileReader.h"
#include "DialogManager.h"
#include "TextureCache.h"
#include "ShapeModel.h"
#include "MainView.h"

CMainView::CMainView()
{
	InitRootLayer();
	m_canvas->DoOnShapeRectChanged(boost::bind(&CMainView::ChangeShapeRect, this, _1, _2));
}


CMainView::~CMainView()
{
}

std::shared_ptr<CParentLayer> const & CMainView::GetRoot() const
{
	return m_root;
}

std::shared_ptr<CCanvas> const & CMainView::GetCanvas() const
{
	return m_canvas;
}

void CMainView::SetNewShapeList(std::vector<std::shared_ptr<SModelShape>> & shapes)
{
	m_canvas->SetNewShapesList(shapes);
}

void CMainView::SetDocDataState(bool isSaved)
{
	m_dataWasChange = !isSaved;
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

void CMainView::ChangeShapeRect(size_t number, CBoundingRect const & rect)
{
	m_onChangedRect(number, rect.position, rect.size);
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

	m_onShapeAdd(type, position);
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

	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&CMainView::Undo, this), UNDO_PATH));
	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&CMainView::Redo, this), REDO_PATH));

	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&CMainView::OpenNewFile, this), OPEN_PATH));
	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&CMainView::SaveCurrentState, this), SAVE_PATH));
	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&CMainView::CreateNewFile, this), NEW_PATH));
	
	m_root->AddChild(m_canvas);
}

void CMainView::InitCanvas()
{
	m_canvas = std::make_shared<CCanvas>();
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

void CMainView::DoOnShapeAdded(std::function<void(ShapeType, Vec2)> const & action)
{
	m_onShapeAdd.connect(action);
}

void CMainView::DoOnDeleteShape(std::function<void(size_t)> const & action)
{
	m_onDeleteShape.connect(action);
}

void CMainView::DoOnRedo(std::function<void()> const & action)
{
	m_onRedo.connect(action);
}

void CMainView::DoOnUndo(std::function<void()> const & action)
{
	m_onUndo.connect(action);
}

void CMainView::DoOnSave(std::function<void(const std::string&)> const & action)
{
	m_onSave.connect(action);
}

void CMainView::DoOnOpen(std::function<void(const std::string&)> const & action)
{
	m_onOpen.connect(action);
}

void CMainView::DoOnCreate(std::function<void()> const & action)
{
	m_onCreate.connect(action);
}

void CMainView::DoOnChangeShapeRect(std::function<void(size_t, Vec2, Vec2)> const & action)
{
	m_onChangedRect.connect(action);
}

std::shared_ptr<CToolbar> CMainView::CreateToolbar()
{
	auto toolbar = std::make_shared<CToolbar>();
	toolbar->SetPosition(TOOLBAR_POSITION);
	toolbar->SetSize(TOOLBAR_SIZE);
	toolbar->SetColor(color::YELLOW);
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
	default:
		break;
	}
}