#pragma once
#include"tools.h"
#include "path.h"
class AI
{
	

private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f view;
	float speedMax;
	float forceMax;
	int masse;
	float angle;
	float timerAI;
	int FrameX;
	IntRect AIrect;
	sf::CircleShape triangle;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape line;
public:
	AI();
	AI(sf::Vector2f _pos);
	~AI();

	void applyForce(sf::Vector2f _force) {
		acceleration.x += _force.x / masse;
		acceleration.y += _force.y / masse;
	}
	void update(sf::Vector2f _posToFollow, path _Path, std::vector<AI*> _vectorAgent);
	sf::Vector2f seek(sf::Vector2f _posToFollow);
	sf::Vector2f arrive(sf::Vector2f _posToFollow);
	sf::Vector2f pathFollowing(path Path);
	void draw(sf::RenderWindow& _window);
	sf::Vector2f separate(std::vector<AI*> other);
	sf::Vector2f getPosition() { return position; }
	sf::Vector2f getVelocity() { return velocity; }
	sf::Vector2f flocking(std::vector<AI*> other);
	sf::Vector2f alignment(std::vector<AI*> other);
	sf::Vector2f cohesion(std::vector<AI*> other);
	sf::Vector2f foramtionV(std::vector<AI*> other);
};

