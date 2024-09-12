#pragma once
#include"tools.h"
#include"Player.h"
class Lighting
{
public :

	Lighting(Player* _player);
	Lighting();
	~Lighting() {};

	void updateLighting();
	sf::Shader shader;
private :
	sf::Vector3f posLight = { 0,0,1 };
	Player* player;
};

