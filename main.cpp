// ShapeManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Controller.h"
int main()
{
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
	auto controller = std::make_unique<CController>(&window);
	controller->Start();
	/*CParentLayer root({ 800, 600 });

	auto toolbar = std::make_shared<CToolbar>();
	toolbar->SetPosition({ 0, 0 });
	toolbar->SetSize({ 800, 100 });
	toolbar->SetColor(SColor(255, 255, 0, 255));
	root.AddChild(toolbar);

	auto foo = [](CCanvas * canvas, ShapeType type) {canvas->CreateShape(type); };

	auto canvas = std::make_shared<CCanvas>();
	canvas->SetPosition({ 5, 105 });
	canvas->SetSize({ 790, 490 });
	canvas->SetColor(SColor(255, 255, 255, 255));
	root.AddChild(canvas);


	auto btn = std::make_shared<CActionButton>();
	btn->SetSize({ 80, 80 });
	btn->SetPosition({ 10, 10 });
	btn->SetColor(SColor(255, 0, 0, 255));
	btn->SetTexturePath("./res/circle.png");
	btn->SetAction(std::bind(foo, canvas.get(), ShapeType::Circle));
	toolbar->AddChild(btn);

	auto btn1 = std::make_shared<CActionButton>();
	btn1->SetSize({ 80, 80 });
	btn1->SetPosition({ 10, 10 });
	btn1->SetColor(SColor(255, 0, 0, 255));
	btn1->SetTexturePath("./res/square.png");
	
	btn1->SetAction(std::bind(foo, canvas.get(), ShapeType::Rectangle));
	toolbar->AddChild(btn1);

	auto btn2 = std::make_shared<CActionButton>();
	btn2->SetSize({ 80, 80 });
	btn2->SetPosition({ 10, 10 });
	btn2->SetColor(SColor(255, 0, 0, 255));
	btn2->SetTexturePath("./res/triangle.png");

	btn2->SetAction(std::bind(foo, canvas.get(), ShapeType::Triangle));
	toolbar->AddChild(btn2);

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
			if (event.type == sf::Event::Closed)
				window.close();
		}
		view.Draw(&root);
		view.DrawShapes(canvas->GetShapes());
		view.DrawSelectFrame(canvas->GetFSelectFrame());
		window.display();
		window.clear();
	}*/
    return 0;
}

