// ShapeManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SceneView.h"
#include "Layer.h"
#include "ActionButton.h"

int main()
{
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
	CLayer layer({ 800, 100 });
	CActionButton btn;
	btn.SetSize({ 80, 80 });
	btn.SecPosition({ 10, 10 });
	layer.SecPosition({ 0, 20 });
	layer.SetColor(SColor(255, 255, 0, 255));
	btn.SetColor(SColor(255, 0, 0, 255));
	btn.SetAction([]() {std::cout << "was clicked" << std::endl; });
	layer.AddChild(&btn);
	CSceneView view(&window);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
			{
				auto test = static_cast<CActionButton*>(layer.GetClickedLayer({ mousePos.x, mousePos.y }));
				test->DoClickAction();
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}
		view.Draw(&layer);
		window.display();
		window.clear();
	}
    return 0;
}

