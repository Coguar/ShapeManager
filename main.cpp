// ShapeManager.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Controller.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(unsigned int (MAIN_WINDOW_SIZE.x), unsigned int(MAIN_WINDOW_SIZE.y)), "ShapeManager", sf::Style::Close, settings);
	auto controller = std::make_unique<CController>(&window);
	controller->Start();
    return 0;
}

