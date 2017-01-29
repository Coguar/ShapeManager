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

std::shared_ptr<CCanvas> const & CMainView::GetCanvas() const
{
	return m_canvas;
}

void CMainView::SetNewShapeList(std::vector<std::shared_ptr<SModelShape>> const & shapes)
{
	m_canvas->SetNewShapesList(shapes);
}

void CMainView::SetEvent(EventType type)
{
	m_event = SEvent(type);
	if (type == EventType::AddCircle || type == EventType::AddRectangle || type == EventType::AddTriangle)
	{
		auto size = m_canvas->GetSize();
		auto pos = m_canvas->GetPosition();
		m_event.m_newRect.position = { pos.x + size.x / 2.0, pos.y + size.y / 2.0 };
	}
}

void CMainView::SetDocDataState(bool isSaved)
{
	m_dataWasChange = !isSaved;
}

SEvent CMainView::GetChangedData() const
{
	return m_event;
}


void CMainView::OpenNewFile()
{
	if (SaveChangesDialog())
	{
		auto path = CDialogManager::GetFileToOpen();
		if (!path.empty())
		{
			m_event = SEvent(EventType::Open);
			m_event.m_filePath = path;
		}
	}
}

bool CMainView::SaveCurrentState()
{
	auto path = CDialogManager::GetFileToSave();
	if (!path.empty())
	{
		m_event = SEvent(EventType::Save);
		m_event.m_filePath = path;
		NotifyObservers();
		m_dataWasChange = false;
		return true;
	}
	return false;
}

void CMainView::CreateNewFile()
{
	if (SaveChangesDialog())
	{
		m_event = SEvent(EventType::Open);
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

void CMainView::InitRootLayer()
{
	m_root = std::make_shared<CParentLayer>(MAIN_WINDOW_SIZE);
	InitCanvas();

	auto toolbar = CreateToolbar();
	m_root->AddChild(toolbar);

	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&CMainView::SetEvent, this, EventType::AddCircle), CIRCLE_PATH));
	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&CMainView::SetEvent, this, EventType::AddRectangle), RECTANGLE_PATH));
	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&CMainView::SetEvent, this, EventType::AddTriangle), TRIANGLE_PATH));

	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&CMainView::SetEvent, this, EventType::Undo), UNDO_PATH));
	toolbar->AddChild(CreateButton(DEFAULT_BUTTONN_SIZE, color::WHITE, std::bind(&CMainView::SetEvent, this, EventType::Redo), REDO_PATH));

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
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(unsigned int(MAIN_WINDOW_SIZE.x), unsigned int(MAIN_WINDOW_SIZE.y)), "ShapeManager", sf::Style::Close, settings);

	while (window.isOpen())
	{
		m_event = SEvent();
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
		if (m_event.m_type == EventType::NotEvent)
		{
			m_event = m_canvas->GetLastEvent();
		}
		CheckEvent();
		m_root->Update();
		window.clear();
		m_root->Draw(&window, &cache);
		window.display();
	}
}

void CMainView::CheckEvent()
{
	if (m_event.m_type != EventType::NotEvent)
	{
		NotifyObservers();
		m_event = SEvent();
	}
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
		m_event = SEvent(EventType::DeleteShape, m_canvas->GetSelectedShapeNum());
		break;
	default:
		break;
	}
}