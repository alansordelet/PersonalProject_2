#include "AI.h"

AI::AI()
{
	position = { 100.0f,100.0f };
	acceleration = { 0.0f,0.0f };
	velocity = { 0.0f,0.0f };
	speedMax = 0.3;
	forceMax = 0.001;
	angle = 0.0f;
	triangle.rotate(angle);
	masse = 5;
	triangle.setRadius(20.0f);
	triangle.setOrigin(20, 20);
	triangle.setPosition(position);
}

AI::AI(sf::Vector2f _pos)
{
	texture.loadFromFile("..\\Ressources\\Textures\\ScaryMan.png");
	sprite.setTexture(texture);
	position = _pos;
	masse = 5;
	acceleration = { 0.0f,0.0f };
	speedMax = 0.2;

	sf::Vector2f random = { (float)(rand() % 2), (float)(rand() % 2) };
	tools::limitVectorFloat(random, speedMax);
	velocity = { sf::Vector2f(random) };

	forceMax = 0.003;
	view = { 40.0f,40.0f };
	angle = 0.0f;
	timerAI = 0;
	FrameX = 0;
	AIrect = {0,0,16,15};

	/*texture.loadFromFile("..\\ressources\\delegue.png");
	triangle.setTexture(&texture);*/
	triangle.setRadius(5.0f);
	triangle.setOrigin(5.0f, 5.0f);
	sprite.setOrigin(8.f, 7.5f);
	triangle.setPosition(position);

}

AI::~AI()
{
}

void AI::update(sf::Vector2f _posToFollow, path _Path, std::vector<AI*> _vectorAgent) {

	sf::Vector2f seekForce;
	timerAI += tools::GetTimeDelta();
	seekForce = seek(pathFollowing(_Path));
	applyForce(separate(_vectorAgent));
	applyForce(separate(_vectorAgent));

	sf::Vector2f tmp1 = velocity;

	applyForce(seekForce);
	velocity += acceleration;
	tools::limitVectorFloat(velocity, speedMax);

	sf::Vector2f tmp2 = velocity;

	position += velocity;
	acceleration = { 0,0 };

	if (position.x > 1800)
		position.x = 0;
	else if (position.x < 0)
		position.x = 1800;
	if (position.y > 900)
		position.y = 0;
	else if (position.y < 0)
		position.y = 900;

	if (timerAI > 0.1)
	{
		FrameX++;
		if (FrameX > 5) FrameX = 0;
		AIrect.left = FrameX * AIrect.width;
		sprite.setTextureRect(AIrect);
		timerAI = 0;
	}

	triangle.setPosition(position);
	sprite.setPosition(position);
}

sf::Vector2f AI::seek(sf::Vector2f _posToFollow) {
	tools::subtract2Vector(_posToFollow, position);

	sf::Vector2f desired = _posToFollow;
	desired = tools::normalize(desired);
	tools::multipleVectorFloat(desired, speedMax);
	tools::subtract2Vector(desired, velocity);

	sf::Vector2f steering = desired;
	tools::limitVectorFloat(steering, forceMax);

	return steering;
}

sf::Vector2f AI::separate(std::vector<AI*> other) {
	float separation = 40.0f;
	sf::Vector2f sum = { 0.0f,0.0f };
	int count = 0;
	sf::Vector2f actualPosition = position;

	for (auto _o : other) {
		float distance = tools::distance(actualPosition, _o->getPosition());
		if (distance > 0 && distance <= separation) {
			tools::subtract2Vector(actualPosition, _o->getPosition());
			actualPosition = tools::normalize(actualPosition);
			tools::divisionVectorFloat(actualPosition, distance);
			tools::ajout2Vector(sum, actualPosition);
			count++;
		}
	}
	if (count > 0) {
		tools::divisionVectorFloat(sum, count);
		sum = tools::normalize(sum);
		tools::multipleVectorFloat(sum, speedMax);
		tools::subtract2Vector(sum, velocity);
		tools::limitVectorFloat(sum, forceMax);
	}
	return Vector2f(sum);
}

sf::Vector2f AI::arrive(sf::Vector2f _posToFollow) {
	sf::Vector2f desired = { _posToFollow.x - position.x, _posToFollow.y - position.y };

	float distance = std::sqrt((std::pow(desired.x, 2) + (std::pow(desired.y, 2))));

	if (distance < 300) {
		float magnitude = tools::map(distance, 0, 300, 0, speedMax);
		desired = tools::normalize(desired);
		tools::multipleVectorFloat(desired, magnitude);
	}
	else {
		desired = tools::normalize(desired);
		tools::multipleVectorFloat(desired, speedMax);
	}
	tools::subtract2Vector(desired, velocity);
	sf::Vector2f steering = desired;

	tools::limitVectorFloat(steering, forceMax);
	return steering;
}

sf::Vector2f AI::pathFollowing(path Path) {
	sf::Vector2f predict = velocity;
	tools::normalize(predict);
	tools::multipleVectorFloat(predict, 20);
	sf::Vector2f a;
	sf::Vector2f b;

	sf::Vector2f predictLoc{ position.x + velocity.x, position.y + velocity.y };
	float tmpDistance = 2000.f;
	sf::Vector2f goodLine{ 0.f,0.f };

	for (int i = 0; i < Path.points.size() - 1; i++) {
		
		a = Path.points[/*static_cast<std::vector<sf::Vector2f, std::allocator<sf::Vector2f>>::size_type>*/(i)];
		b = Path.points[/*static_cast<std::vector<sf::Vector2f, std::allocator<sf::Vector2f>>::size_type>*/(i) + 1];
		sf::Vector2f target;

		target = tools::scalaireProjection(predictLoc, a, b);
		if (target.x < a.x /*&& target.y < a.y*/ || target.x > b.x/* && target.y > b.y*/)
			target = b;
		if (tmpDistance > tools::distance(predictLoc, target)) {
			tmpDistance = tools::distance(predictLoc, target);
			goodLine = b;
			tools::subtract2Vector(b, a);
			target = b;
			target = tools::normalize(target);
			tools::multipleVectorFloat(target, 40);
			tools::ajout2Vector(goodLine, target);
		}
		
	}

	return goodLine;
}
void AI::draw(sf::RenderWindow& _window) {
	//_window.draw(line);
	//_window.draw(triangle);
	_window.draw(sprite);
}