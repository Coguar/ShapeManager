// ShapeManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SceneView.h"
//#include "Layer.h"
#include "Toolbar.h"
#include "ActionButton.h"
#include "Canvas.h"
int main()
{
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
	CParentLayer root({ 800, 600 });

	auto toolbar = std::make_shared<CToolbar>();
	toolbar->SetPosition({ 0, 0 });
	toolbar->SetSize({ 800, 100 });
	toolbar->SetColor(SColor(255, 255, 0, 255));
	root.AddChild(toolbar);

	auto btn = std::make_shared<CActionButton>();
	btn->SetSize({ 80, 80 });
	btn->SetPosition({ 10, 10 });
	btn->SetColor(SColor(255, 0, 0, 255));
	btn->SetAction([]() {std::cout << "was clicked" << std::endl; });
	toolbar->AddChild(btn);

	auto canvas = std::make_shared<CCanvas>();
	canvas->SetPosition({ 5, 105 });
	canvas->SetSize({ 790, 490 });
	canvas->SetColor(SColor(255, 255, 255, 255));
	root.AddChild(canvas);

	canvas->CreateShape(ShapeType::Circle);
	canvas->CreateShape(ShapeType::Rectangle);
	canvas->CreateShape(ShapeType::Triangle);

	CSceneView view(&window);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			root.DispatchEvent(event);
			/*auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			auto item = root.GetClickedLayer({ mousePos.x, mousePos.y });
			if(item)
				item->OnEvent(event);*/
			/*if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
			{
				root.GetClickedLayer({ mousePos.x, mousePos.y });
			}*/
			if (event.type == sf::Event::Closed)
				window.close();
		}
		view.Draw(&root);
		view.DrawShapes(canvas->GetShapes());
		view.DrawSelectFrame(canvas->GetFSelectFrame());
		window.display();
		window.clear();
	}
    return 0;
}

