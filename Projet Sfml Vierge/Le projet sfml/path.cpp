#include "path.h"

path::path()
{
	/*start = { 0.0f, 500.0f };
	end = { 1920.0f, 500 };*/
	size = 1;
	/*points.push_back({ 0.0f, 500.0f });
	points.push_back({ 700,200 });
	points.push_back({ 1300,800 });
	points.push_back({ 1920.0f, 500 });*/
	circle.setRadius({ 10.0f });
	circle.setOrigin(10, 10);
	circle.setFillColor(sf::Color::Blue);
	timerpath = 0;
}

path::~path()
{

}

void path::randomPoint()
{
	points.clear();
	float random = (int)rand() % 900 + 100;
	points.push_back({ 0.0f, 500.0f });
	points.push_back({ 500, random });
	random = rand() % 900 + 100;
	points.push_back({ 1000,random });
	random = rand() % 900 + 100;
	points.push_back({ 1500, random });
	points.push_back({ 1920.0f, 500 });
}

void path::PlacePoints(sf::RenderWindow& _window)
{
	timerpath += tools::GetTimeDelta();
	sf::Vector2i mouse = sf::Mouse::getPosition(_window);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timerpath > 0.5) //clique gauche pour posé les points
	{
		points.push_back(sf::Vector2f(mouse.x, mouse.y));
		timerpath = 0;
	}
}

void path::draw(sf::RenderWindow& _window)
{
	PlacePoints(_window);
	//circle.setPosition(start);
	//_window.draw(circle);
	for (auto _i : points) {

		circle.setPosition(_i);
		_window.draw(circle);
	}
	//circle.setPosition(end);
	//_window.draw(circle);
}
