#include "Player.h"

Player::Player(Maps* _map)
{
	map = _map;
	texturePlayer.loadFromFile("..\\Ressources\\Textures\\Player.png");
	textureHearts.loadFromFile("..\\Ressources\\Textures\\Hearts.png");
	textureDeath.loadFromFile("..\\Ressources\\Textures\\DeadMan.png");
	texturePlank.loadFromFile("..\\Ressources\\Textures\\plank.png");

	spriteHearts.setTexture(textureHearts);
	spritePlank.setTexture(texturePlank);
	pos.x = 50;
	pos.y = 100;
	speed = { 100,100 };
	rectPlayer = { 0,0,64,64 };
	spritePlayer.setTextureRect(rectPlayer);
	spriteHearts.setTextureRect(rectHearts);
	spriteHearts.setPosition(-300, 125);
	spritePlank.setColor(sf::Color(100, 20, 20,150));

	spritePlank.setPosition(-470, -150);
	spritePlayer.setScale(Vector2f(0.4, 0.4));
	spritePlank.setScale(Vector2f(0.8, 0.8));

	timerPlayer = 0;
	frameX = 0;
	frameY = 0;
	font.loadFromFile("..\\Ressources\\bloody.ttf");
}

Player::~Player()
{
}

void Player::update()
{
	timerPlayer += tools::GetTimeDelta();
	if (isMoving == true && death == false)
	{
		if (timerPlayer > 0.1)
		{
			frameX++;
			if (frameX > 8) frameX = 0;
			rectPlayer.left = frameX * rectPlayer.width;
			rectPlayer.top = frameY * rectPlayer.height;
			spritePlayer.setTextureRect(rectPlayer);
			timerPlayer = 0;
		}
	}

	isMoving = false;

	if (map->gotSpell == false)
		tilenb = 0;
	else
		tilenb = 1;

	if (map->gotTime == false)
		tilenb2 = 2;
	else
		tilenb2 = 1;

	if (map->gotCloak == false)
		tilenb3 = 3;
	else
		tilenb3 = 1;



	if (death == false)
	{
		spritePlayer.setTexture(texturePlayer);
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			//directionu = UPS;
			if (!collisionMapPlayer(spritePlayer.getGlobalBounds(), UPS, speed, 1, tilenb, tilenb2, tilenb3))
			{
				frameY = 0;
				pos.y -= speed.y * tools::GetTimeDelta();
				isMoving = true;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::A) && !thirdspawn)
		{
			//directionu = LEFTS;
			if (!collisionMapPlayer(spritePlayer.getGlobalBounds(), LEFTS, speed, 1, tilenb, tilenb2, tilenb3))
			{
				frameY = 1;
				pos.x -= speed.x * tools::GetTimeDelta();
				isMoving = true;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::S) && !thirdspawn)
		{
			//directionu = DOWNS;
			if (!collisionMapPlayer(spritePlayer.getGlobalBounds(), DOWNS, speed, 1, tilenb, tilenb2, tilenb3))
			{
				frameY = 2;
				pos.y += speed.y * tools::GetTimeDelta();
				isMoving = true;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::D) && !thirdspawn)
		{
			//directionu = RIGHTS;
			if (!collisionMapPlayer(spritePlayer.getGlobalBounds(), RIGHTS, speed, 1, tilenb, tilenb2, tilenb3))
			{
				frameY = 3;
				pos.x += speed.x * tools::GetTimeDelta();
				isMoving = true;
			}
		}
	}
	else if (death == true)
	{
		spritePlayer.setTexture(textureDeath);
		rectPlayer.left = 0;
		rectPlayer.top = 0;
		frameY = 0;
		frameX = 0;
		
	}

	spritePlayer.setPosition(pos);


}

void Player::Display(RenderWindow& _window, sf::Shader* shader)
{

	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", sf::Vector2f(pos.x + 15, pos.y + 5));
		shader->setUniform("distance", LightIncrease);
	}

	DisplayMap(_window, shader);
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(spritePlayer.getGlobalBounds().width, spritePlayer.getGlobalBounds().height));
	rect.setPosition(sf::Vector2f(spritePlayer.getGlobalBounds().left, spritePlayer.getGlobalBounds().top));
	rect.setOutlineColor(sf::Color::Red);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(2);
	//_window.draw(rect);

	if (spritePlayer.getGlobalBounds().intersects(map->SpellS.getGlobalBounds()))
	{
		
	}
	if (spritePlayer.getGlobalBounds().intersects(map->clockS.getGlobalBounds()))
	{
		
	}
	if (spritePlayer.getGlobalBounds().intersects(map->cloakS.getGlobalBounds()))
	{
		thirdspawn = true;
		map->gotCloak = true;
		map->cloakS.setPosition(-500, 0);
	}
	

	std::vector<MyFlashlights*>::iterator it = map->flashlights.begin();
	while (it != map->flashlights.end()) {
		if (spritePlayer.getGlobalBounds().intersects((*it)->flashlightS.getGlobalBounds())) {
			delete* it;
			it = map->flashlights.erase(it);
			LightIncrease -= 0.2;
			BigTimer += 25;
		}
		else {
			++it;
		}
	}


}

void Player::ViewManager(Player& _player, sf::RenderWindow& _window, stateManager& _state)
{

	if (stateManager::state == enumState::EDITOR)
	{
		_window.setView(map->viewGame);

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			map->posView.x -= 400 * tools::GetTimeDelta();
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			map->posView.x += 400 * tools::GetTimeDelta();
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			map->posView.y += 400 * tools::GetTimeDelta();
		}
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			map->posView.y -= 400 * tools::GetTimeDelta();
		}
		map->viewGame.setCenter(map->posView);
	}
	if (stateManager::state == enumState::GAME)
	{
		_window.setView(map->viewGame);
		map->viewGame.setSize(300, 200);
		sf::Vector2f currentPos = map->viewGame.getCenter();
		sf::Vector2f targetPos = sf::Vector2f(_player.GetPos().x + 15, _player.GetPos().y);
		sf::Vector2f distance = targetPos - currentPos;
		float smoothingFactor = 0.1f;
		map->viewGame.setCenter(currentPos + smoothingFactor * distance);

	}

}

void Player::DisplayMap(sf::RenderWindow& _window, sf::Shader* shader)
{

	sf::RenderTexture tileTexture;
	sf::RenderTexture tileTexture2;
	tileTexture.create(1920, 1920);
	tileTexture2.create(1920, 1920);

	// draw tiles to the texture
	tileTexture.clear();
	tileTexture2.clear();
	for (const auto& _o : map->layer1) {
		sf::IntRect tmpRect{ (_o.tile % 16) * 16, (_o.tile / 16) * 16, 16, 16 };
		map->spriteMap.setTextureRect(tmpRect);
		map->spriteMap.setPosition(_o.position);
		tileTexture.draw(map->spriteMap);
	}
	/*for (const auto& _o : map->layer3) {
		sf::IntRect tmpRect{ (_o.tile % 16) * 16, (_o.tile / 16) * 16, 16, 16 };
		map->HitboxS.setTextureRect(tmpRect);
		map->HitboxS.setPosition(_o.position);
		tileTexture.draw(map->HitboxS);
	}*/


	tileTexture2.display();

	// draw the texture to the window

	if (shader)
		tileTexture.draw(spritePlayer, shader);
	for (const auto& _o : map->layer2) {
		sf::IntRect tmpRect{ (_o.tile % 16) * 16, (_o.tile / 16) * 16, 16, 16 };
		map->spriteMap2.setTextureRect(tmpRect);
		map->spriteMap2.setPosition(_o.position);
		tileTexture.draw(map->spriteMap2);
	}
	tileTexture.display();
	sf::Sprite tileSprite(tileTexture.getTexture());
	if (map->gotTime == false)
		_window.draw(tileSprite);
	if (map->gotTime == true)
		_window.draw(tileSprite, shader);
}

void Player::DisplayHUD(sf::RenderWindow& _window)
{
	_window.draw(spritePlank);
	spriteHearts.setScale(sf::Vector2f(5, 5));
	_window.draw(spriteHearts);
	
	rectHearts.left = frameXH * rectHearts.width;
	spriteHearts.setTextureRect(rectHearts);

	if (map->gotTime == true)
	{
		countdownTimer += tools::GetTimeDelta();
		secondsRemaining = BigTimer - countdownTimer;
		int minutes = secondsRemaining / 60;
		int seconds = secondsRemaining % 60;
		sf::Text text;
		text.setFont(font);
		text.setFillColor(sf::Color::Red);
		text.setPosition(-350, 40);
		text.setCharacterSize(50);
		text.setString(std::to_string(minutes) + "m " + std::to_string(seconds));
		_window.draw(text);
	}

}

bool Player::collisionMapPlayer(FloatRect _MaleSprite, DirectionPlayer _direction, Vector2f _vitesse, int _tilenb, int _tilenb2, int _tilenb3, int _tilenb4)
{

	bool collisionDetected = false;
	if (_direction == UPS)
	{
		MaleSprite.x = (int)_MaleSprite.left / 16;
		MaleSprite.y = (int)(_MaleSprite.top - _vitesse.y * tools::GetTimeDelta()) / 16;
		MaleSprite2.x = (int)(_MaleSprite.left + _MaleSprite.width) / 16;
		MaleSprite2.y = (int)(_MaleSprite.top - _vitesse.y * tools::GetTimeDelta()) / 16;

		for (const auto& mapTile : map->layer3) {
			if ((mapTile.tile == _tilenb || mapTile.tile == _tilenb2 || mapTile.tile == _tilenb3 || mapTile.tile == _tilenb4) &&
				(MaleSprite.x == mapTile.position.x / 16 && MaleSprite.y == mapTile.position.y / 16 ||
					MaleSprite2.x == mapTile.position.x / 16 && MaleSprite2.y == mapTile.position.y / 16)) {
				return true;
			}
		}

	}
	else if (_direction == DOWNS)
	{

		MaleSprite.x = (int)(_MaleSprite.left) / 16;
		MaleSprite.y = (int)((_MaleSprite.top) + _MaleSprite.height + _vitesse.y * tools::GetTimeDelta()) / 16;
		MaleSprite2.x = (int)(_MaleSprite.left + _MaleSprite.width) / 16;
		MaleSprite2.y = (int)((_MaleSprite.top) + _MaleSprite.height + _vitesse.y * tools::GetTimeDelta()) / 16;
		for (const auto& mapTile : map->layer3) {
			if ((mapTile.tile == _tilenb || mapTile.tile == _tilenb2 || mapTile.tile == _tilenb3 || mapTile.tile == _tilenb4) &&
				(MaleSprite.x == mapTile.position.x / 16 && MaleSprite.y == mapTile.position.y / 16 ||
					MaleSprite2.x == mapTile.position.x / 16 && MaleSprite2.y == mapTile.position.y / 16)) {
				return true;
			}
		}

	}
	else if (_direction == LEFTS)
	{
		MaleSprite.x = (int)((_MaleSprite.left) - (_MaleSprite.width / 16) - _vitesse.x * tools::GetTimeDelta()) / 16;
		MaleSprite.y = (int)(_MaleSprite.top / 16);
		MaleSprite2.x = (int)((_MaleSprite.left) - _vitesse.x * tools::GetTimeDelta()) / 16;
		MaleSprite2.y = (int)(_MaleSprite.top + _MaleSprite.height) / 16;
		for (const auto& mapTile : map->layer3) {
			if ((mapTile.tile == _tilenb || mapTile.tile == _tilenb2 || mapTile.tile == _tilenb3 || mapTile.tile == _tilenb4) &&
				(MaleSprite.x == mapTile.position.x / 16 && MaleSprite.y == mapTile.position.y / 16 ||
					MaleSprite2.x == mapTile.position.x / 16 && MaleSprite2.y == mapTile.position.y / 16)) {
				return true;
			}
		}

	}
	else if (_direction == RIGHTS)
	{
		MaleSprite.x = (int)((_MaleSprite.left) + _MaleSprite.width + _vitesse.x * tools::GetTimeDelta()) / 16;
		MaleSprite.y = (int)(_MaleSprite.top) / 16;
		MaleSprite2.x = (int)((_MaleSprite.left) + _MaleSprite.width + _vitesse.x * tools::GetTimeDelta()) / 16;
		MaleSprite2.y = (int)(_MaleSprite.top + _MaleSprite.height) / 16;

		for (const auto& mapTile : map->layer3) {
			if ((mapTile.tile == _tilenb || mapTile.tile == _tilenb2 || mapTile.tile == _tilenb3 || mapTile.tile == _tilenb4) &&
				(MaleSprite.x == mapTile.position.x / 16 && MaleSprite.y == mapTile.position.y / 16 ||
					MaleSprite2.x == mapTile.position.x / 16 && MaleSprite2.y == mapTile.position.y / 16)) {
				return true;
			}
		}

	}
	return false;
}