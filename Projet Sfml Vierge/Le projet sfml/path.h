#pragma once
#include"tools.h"
class path
{
public:
	sf::Vector2f start;
	sf::Vector2f end;
	std::vector<sf::Vector2f> points;
	sf::CircleShape circle;
	float size;
	path();
	~path();
	void randomPoint();
	void PlacePoints(sf::RenderWindow& _window);
	void draw(sf::RenderWindow& _window);
	float timerpath;
};

