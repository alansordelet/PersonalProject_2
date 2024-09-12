#include <iostream>
#include "SFML/Graphics.hpp"
#include "tools.h"
#include "Player.h"
#include "Maps.h"
#include "AI.h"
#include "path.h"
#include "stateManager.h"
#include"Enemy.h"
#include"Lighting.h"
#include"Menu.h"


using namespace sf;
using namespace std;


int main()
{
	RenderWindow window(sf::VideoMode(1920, 1080), "Projet Perso");	
	stateManager states;
	Maps map;
	Player play(&map);
	Enemy enemy(&play);

	Menu menu(&states);
	Lighting light(&play);
	Shader CoreShader;
	if (!CoreShader.loadFromFile("../Ressources/vertex_shader.vert", "../Ressources/fragment_shader.frag"))
	{
		cout << "error";
	}
	states.state = enumState::MENU;
	float timer = 0;
	while (window.isOpen())
	{
		Event event;
		tools::restartClock();
		timer += tools::GetTimeDelta();
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			map.zoom(event);
		}
		if (stateManager::state == enumState::MENU)
		{
			menu.update(window, event);
		}
		if (stateManager::state == enumState::EDITOR)
		{
			map.UpdateMaps(window);
		
		}

		if (stateManager::state == enumState::GAME)
		{
			play.update();
			enemy.UpdateEnemy();
		}
		
		play.ViewManager(play, window, states);
		window.clear();
		
		
		if (stateManager::state == enumState::MENU)
		{
			menu.display(window);
		}
		if (stateManager::state == enumState::EDITOR || stateManager::state == enumState::GAME)
		{
			play.Display(window, &CoreShader);
			map.DisplayMaps(window, &CoreShader);
			enemy.DisplaySpeeches(window, &CoreShader);
		}
		if (stateManager::state == enumState::GAME)
		{
			enemy.DisplayEnemy(window, &CoreShader);
			map.setViewHUD(window);
			play.DisplayHUD(window);
		}
		
		
		window.display();
	}
	map.QuickSave();
	return 0;
}
