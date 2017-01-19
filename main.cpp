// ShapeManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SceneView.h"
//#include "Layer.h"
#include "Toolbar.h"
#include "ActionButton.h"

int main()
{
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
	CLayer root({ 800, 600 });
	std::shared_ptr<CToolbar> toolbar = std::make_shared<CToolbar>();
	std::shared_ptr<CActionButton> btn = std::make_shared<CActionButton>();
	btn->SetSize({ 80, 80 });
	btn->SecPosition({ 10, 10 });
	toolbar->SecPosition({ 0, 20 });
	toolbar->SetSize({ 800, 100 });
	toolbar->SetColor(SColor(255, 255, 0, 255));
	btn->SetColor(SColor(255, 0, 0, 255));
	btn->SetAction([]() {std::cout << "was clicked" << std::endl; });
	toolbar->AddChild(btn);
	root.AddChild(toolbar);
	CSceneView view(&window);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			auto item = root.GetClickedLayer({ mousePos.x, mousePos.y });
			if(item)
				item->OnEvent(event);
			/*if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
			{
				root.GetClickedLayer({ mousePos.x, mousePos.y });
			}*/
			if (event.type == sf::Event::Closed)
				window.close();
		}
		view.Draw(&root);
		window.display();
		window.clear();
	}
    return 0;
}

