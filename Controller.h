#pragma once
#include "AppModel.h"
#include "SceneView.h"

class CController
{
public:
	CController(sf::RenderWindow * target);
	~CController();

	void Start();
	void Draw();
private:
	void OnKeyPressed(sf::Event const&  event);

	std::unique_ptr<CAppModel> m_model;
	std::unique_ptr<CSceneView> m_view;
	sf::RenderWindow * m_target = nullptr;
};

