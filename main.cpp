// ShapeManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Controller.h"
int main()
{
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
	auto controller = std::make_unique<CController>(&window);
	controller->Start();
    return 0;
}

