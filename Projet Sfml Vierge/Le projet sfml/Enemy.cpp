#include "Enemy.h"


Enemy::Enemy(Player* _player)
{
	player = _player;
	blackScreen.setSize(sf::Vector2f(1920, 1080));
	blackScreen.setFillColor(sf::Color::Black);
	blackScreen.setOrigin(blackScreen.getSize() / 2.0f);
	blackScreen.setPosition(1920 / 2.0f, 1080 / 2.0f);
	WarningT.loadFromFile("..\\Ressources\\Textures\\GhostWarning.png");
	
	WarningS.setTexture(WarningT);
	WarningS.setScale(sf::Vector2f(0.06, 0.06));
	WarningS.setColor(sf::Color(255, 255, 255, 255));
	Speeches.push_back(new MySpeeches(sf::Vector2f(60, 310), "speech2.png", sf::Vector2f(0.08, 0.08)));
	Speeches.push_back(new MySpeeches(sf::Vector2f(10, 323), "speech1.png", sf::Vector2f(0.2, 0.2)));
	Speeches.push_back(new MySpeeches(sf::Vector2f(65, 330), "speech5.png", sf::Vector2f(0.06, 0.06)));
	Speeches.push_back(new MySpeeches(sf::Vector2f(160, 90), "speech3.png", sf::Vector2f(0.08, 0.08)));
	Speeches.push_back(new MySpeeches(sf::Vector2f(220, 200), "speech4.png", sf::Vector2f(0.08, 0.08)));
	Speeches.push_back(new MySpeeches(sf::Vector2f(298, 205), "speech6.png", sf::Vector2f(0.08, 0.08)));
	Speeches.push_back(new MySpeeches(sf::Vector2f(685, 180), "speech7.png", sf::Vector2f(0.08, 0.08)));
	Speeches.push_back(new MySpeeches(sf::Vector2f(698, 467), "speech8.png", sf::Vector2f(0.08, 0.08)));
	Speeches.push_back(new MySpeeches(sf::Vector2f(463, 570), "speech9.png", sf::Vector2f(0.08, 0.08)));
	Speeches.push_back(new MySpeeches(sf::Vector2f(326, 605), "speech10.png", sf::Vector2f(0.08, 0.08)));
}

Enemy::Enemy(sf::Vector2f _pos, Direction _firstdirection, bool _reverse)
{
	EnemyT.loadFromFile("..\\Ressources\\Textures\\ScaryMan.png");
	EnemyS.setTexture(EnemyT);
	position = _pos;
	EnemyS.setPosition(position);
	speed = 100;
	direction = _firstdirection;
	reverseSecond = _reverse;
	enemyRect = { 0,0,16,15 };
	EnemyS.setTextureRect(enemyRect);
	enemytimer = 0;
	frameX = 0;
	frameY = 0;

	
}


void Enemy::ActivateDeathScreen(sf::RenderWindow& _window, bool _thisbool)
{

	if (!fadeOut)
	{
		if (gethit == false)
		{
			sounds.playSoundQuick("death");
			gethit = true;
		}
		
		alpha = std::min(alpha + 0.01f, 1.0f);
		if (alpha >= 1.0f)
		{
			fadeOut = true;
		}
	}
	else
	{
		if (player->frameXH > 3)
		{
			sounds.pauseSound("firstsection");
			sounds.pauseSound("secondsection");
			sounds.pauseSound("finalsection");
			sounds.pauseSound("noises");
			playMusic = false;
			secondspawn = false;
			firstspawn = false;
			player->map->gotSpell = false;
			player->map->gotCloak = false;
			player->map->gotTime = false;
			gottimenoise = false;
			gotbooknoise = false;
			enemycontainer.clear();
			stateManager::state = enumState::MENU;
			player->frameXH = 0;
		}
		player->setPos(positionRespawn);
		alpha = std::max(alpha - 0.01f, 0.0f);
		if (alpha <= 0.0f)
		{
			player->frameXH++;
			gethit = false;
			fadeOut = false;
			player->death = false;
		}
	}
	sf::Color color = sf::Color::Black;
	color.a = static_cast<sf::Uint8>(255.0f * alpha);
	blackScreen.setFillColor(color);
	_window.draw(blackScreen);
}

void Enemy::firstMaze()
{
	for (auto n : enemycontainer)
	{
		if (n->position.x >= 838 && n->position.x <= 849 && n->position.y >= 200 && n->position.y <= 280)
		{
			n->direction = DOWN;
		}
		if (n->position.x >= 838 && n->position.x <= 849 && n->position.y >= 430 && n->position.y <= 440)
		{
			n->direction = LEFT;
		}
		if (n->position.x >= 680 && n->position.x <= 687 && n->position.y >= 430 && n->position.y <= 440)
		{
			n->direction = UP;
		}
		if (n->position.x >= 680 && n->position.x <= 695 && n->position.y >= 355 && n->position.y <= 363)
		{
			n->direction = LEFT;
		}
		if (n->position.x >= 585 && n->position.x <= 591 && n->position.y >= 355 && n->position.y <= 363)
		{
			n->direction = DOWN;
		}
		if (n->position.x >= 585 && n->position.x <= 591 && n->position.y >= 540 && n->position.y <= 545)
		{
			n->direction = RIGHT;
		}
		if (n->position.x >= 1160 && n->position.x <= 1165 && n->position.y >= 540 && n->position.y <= 545)
		{
			n->direction = UP;
		}
		if (n->position.x >= 1160 && n->position.x <= 1165 && n->position.y >= 230 && n->position.y <= 234)
		{
			n->direction = LEFT;
		}
		if (n->position.x >= 1095 && n->position.x <= 1102 && n->position.y >= 230 && n->position.y <= 234)
		{
			n->direction = UP;
		}
		if (n->position.x >= 1095 && n->position.x <= 1102 && n->position.y >= 160 && n->position.y <= 169)
		{
			n->direction = LEFT;
		}
		if (n->position.x >= 1018 && n->position.x <= 1023 && n->position.y >= 160 && n->position.y <= 169)
		{
			n->direction = UP;
		}
		if (n->position.x >= 1018 && n->position.x <= 1023 && n->position.y >= 120 && n->position.y <= 125)
		{
			n->direction = RIGHT;
		}
		if (n->position.x >= 1070 && n->position.x <= 1080 && n->position.y >= 120 && n->position.y <= 125)
		{
			n->direction = UP;
		}
		if (n->position.x >= 1070 && n->position.x <= 1080 && n->position.y >= 70 && n->position.y <= 80)
		{
			n->direction = LEFT;
		}
		if (n->position.x >= 969 && n->position.x <= 972 && n->position.y >= 70 && n->position.y <= 80)
		{
			n->direction = DOWN;
		}
		if (n->position.x >= 969 && n->position.x <= 972 && n->position.y >= 330 && n->position.y <= 340)
		{
			n->direction = RIGHT;
		}
		if (n->position.x >= 1116 && n->position.x <= 1119 && n->position.y >= 330 && n->position.y <= 340)
		{
			n->direction = DOWN;
		}
		if (n->position.x >= 1116 && n->position.x <= 1119 && n->position.y >= 431 && n->position.y <= 440)
		{
			n->direction = LEFT;
		}
		if (n->position.x >= 1030 && n->position.x <= 1040 && n->position.y >= 431 && n->position.y <= 440)
		{
			n->direction = DOWN;
		}
		if (n->position.x >= 1030 && n->position.x <= 1040 && n->position.y >= 540 && n->position.y <= 545)
		{
			n->direction = RIGHT;
		}
	}
}

void Enemy::LoopdyLoop()
{
	for (auto n : enemycontainer)
	{
		if (n->position.x >= 482 && n->position.x <= 514 && n->position.y >= 615 && n->position.y <= 626)
		{			
			if (n->reverseSecond == false)
				n->direction = RIGHT;
			else
				n->direction = DOWN;		
		}
		if (n->position.x >= 1132 && n->position.x <= 1164 && n->position.y >= 615 && n->position.y <= 626)
		{
			if (n->reverseSecond == false)
				n->direction = DOWN;
			else
				n->direction = LEFT;
		}
		if (n->position.x >= 1132 && n->position.x <= 1164 && n->position.y >= 775 && n->position.y <= 792)
		{
			if (n->reverseSecond == false)
				n->direction = LEFT;
			else
				n->direction = UP;	
		}
		if (n->position.x >= 482 && n->position.x <= 514 && n->position.y >= 775 && n->position.y <= 792)
		{
			if (n->reverseSecond == false)
				n->direction = UP;
			else
				n->direction = RIGHT;
		}
	}
}

void Enemy::secondMaze()
{
	for (auto n : enemycontainer)
	{
		if (n->position.x >= 200 && n->position.x <= 206 && n->position.y >= 650 && n->position.y <= 670)
		{
			n->speed = 100;
			n->reverseSecond = false;  
			n->direction = DOWN;
		}
		if (n->position.x >= 200 && n->position.x <= 206 && n->position.y >= 821 && n->position.y <= 827)
		{
			n->speed = 100;
			if (n->reverseSecond == false)
				n->direction = LEFT;
			else
				n->direction = UP;
		}
		if (n->position.x >= 133 && n->position.x <= 137 && n->position.y >= 821 && n->position.y <= 827)
		{
			n->speed = 100;
			if (n->reverseSecond == false)
			n->direction = DOWN;
			else
				n->direction = RIGHT;
		}
		if (n->position.x >= 133 && n->position.x <= 137 && n->position.y >= 890 && n->position.y <= 900)
		{
			n->speed = 100;
			if (n->reverseSecond == false)
			n->direction = LEFT;
			else
				n->direction = UP;
		}
		if (n->position.x >= 47 && n->position.x <= 53 && n->position.y >= 890 && n->position.y <= 900)
		{
			n->speed = 100;
			if (n->reverseSecond == false)
			n->direction = DOWN;
			else
				n->direction = RIGHT;
		}
		if (n->position.x >= 47 && n->position.x <= 53 && n->position.y >= 1133 && n->position.y <= 1138)
		{
			n->speed = 100;
			if (n->reverseSecond == false)
			n->direction = RIGHT;
		   else
			n->direction = UP;
		}
		if (n->position.x >= 160 && n->position.x <= 166 && n->position.y >= 1133 && n->position.y <= 1138)
		{
			n->speed = 100;
			if (n->reverseSecond == false)
			n->direction = DOWN;
			else
				n->direction = LEFT;
		}
		if (n->position.x >= 160 && n->position.x <= 166 && n->position.y >= 1303 && n->position.y <= 1307)
		{
			n->speed = 100;
			if (n->reverseSecond == false)
			n->direction = RIGHT;
			else
				n->direction = UP;
		}
		if (n->position.x >= 270 && n->position.x <= 280 && n->position.y >= 1303 && n->position.y <= 1307)
		{
			n->speed = 100;
			if (n->reverseSecond == false)
			n->direction = UP;
			else
				n->direction = LEFT;
		}
		if (n->position.x >= 270 && n->position.x <= 280 && n->position.y >= 885 && n->position.y <= 895)
		{
			n->speed = 150;
			if (n->reverseSecond == false)
			n->direction = RIGHT;
			else
				n->direction = DOWN;
		}
		if (n->position.x >= 1028 && n->position.x <= 1047 && n->position.y >= 885 && n->position.y <= 895)
		{
			n->speed = 200;
			if (n->reverseSecond == false)
				n->direction = DOWN;
			else
				n->direction = LEFT;
			
		}
		if (n->position.x >= 1028 && n->position.x <= 1047 && n->position.y >= 1600 && n->position.y <= 1700)
		{
			n->speed = 200;
			n->direction = UP;
			n->reverseSecond = true;
		}
	}
}

void Enemy::UpdateEnemy()
{
	sounds.setSoundVolumeSOUND("alert", 25);
	
	if (playMusic == false)
	{
		sounds.loadSound("alert", "alert.ogg");
		sounds.loadSound("firstsection", "firstsection.wav");
		sounds.loadSound("death", "death.wav");
		sounds.loadSound("secondsection", "secondsection.wav");
		sounds.loadSound("noises", "noises.wav");
		sounds.loadSound("finalsection", "FinalSection.wav");
		sounds.loadSound("poweroff", "poweroff.wav");
		sounds.loadSound("booksound", "booksound.wav");
		sounds.playSoundQuick("firstsection");
		sounds.setSoundLoop("firstsection", true);
		sounds.setSoundLoop("secondsection", true);
		sounds.setSoundLoop("noises", true);
		sounds.setSoundLoop("finalsection", true);
		playMusic = true;
	}
	sounds.playSoundRandom("noises", 60, 60);
	spawntimer += tools::GetTimeDelta();
	if (Keyboard::isKeyPressed(Keyboard::Space) && spawntimer > 0.2)
	{
		enemycontainer.push_back(new Enemy(sf::Vector2f(340, 660), LEFT, false));
		spawntimer = 0;
	}
	if (player->GetPos().x >= 800 && player->GetPos().x <= 900 && player->GetPos().y >= 275 && player->GetPos().y <= 290 && firstspawn == false)
	{
		enemycontainer.push_back(new Enemy(sf::Vector2f(800, 210), RIGHT, false));
		firstspawn = true;
	}
	if (player->GetPos().x >= 550 && player->GetPos().x <= 580 && player->GetPos().y >= 620 && player->GetPos().y <= 680 && secondspawn == false)
	{	
		enemycontainer.push_back(new Enemy(sf::Vector2f(440, 620), RIGHT, false));
		enemycontainer.push_back(new Enemy(sf::Vector2f(440, 620), RIGHT, true));
		secondspawn = true;
	}
	if (player->thirdspawn == true)
	{
		timerspawnthem += tools::GetTimeDelta();
		if (timerspawnthem > 1.5)
		{
			howmany+= 1;
			if (howmany < 4)
			{
				enemycontainer.push_back(new Enemy(sf::Vector2f(340, 660), LEFT, false));
			}
			else
			{
				player->thirdspawn = false;
			}
			timerspawnthem = 0;
		}
		
		
	}

	if (player->spritePlayer.getGlobalBounds().intersects(player->map->clockS.getGlobalBounds()))
	{
		player->map->gotTime = true;
		if (gottimenoise == false)
		{
			sounds.playSound("poweroff");
			gottimenoise = true;
		}
		
	}
	if (player->spritePlayer.getGlobalBounds().intersects(player->map->SpellS.getGlobalBounds()))
	{
		player->map->gotSpell = true;
		if (gotbooknoise == false)
		{
			sounds.playSound("booksound");
			gotbooknoise = true;
		}
	}
	if (player->spritePlayer.getGlobalBounds().intersects(player->map->doorS.getGlobalBounds()) || player->BigTimer < 1)
	{
		sounds.pauseSound("finalsection");
		sounds.pauseSound("noises");
		playMusic = false;
		secondspawn = false;
		firstspawn = false;
		player->map->gotSpell = false;
		player->map->gotCloak = false;
		player->map->gotTime = false;
		gottimenoise = false;
		gotbooknoise = false;
		enemycontainer.clear();
		stateManager::state = enumState::MENU;
	}


	if (player->map->gotSpell == false)
	{
		positionRespawn = { 700,200 };
		firstMaze();
	}
	if (player->map->gotCloak == false && player->map->gotSpell == true)
	{
		sounds.pauseSound("firstsection");
		sounds.playSoundOnce("secondsection");
		positionRespawn = { 440,640 };
		LoopdyLoop();
	}
	if (player->map->gotCloak == true)
	{
		sounds.pauseSound("secondsection");
		sounds.playSoundOnce2("finalsection");
		secondMaze();
	}

	for (auto n : enemycontainer)
	{
		n->enemytimer += tools::GetTimeDelta();
		if (n->enemytimer > 0.1)
		{
			n->frameX++;
			if (n->frameX > 5) n->frameX = 0;
			n->enemyRect.left = n->frameX * n->enemyRect.width;
			n->enemyRect.top = n->frameY * n->enemyRect.height;
			n->EnemyS.setTextureRect(n->enemyRect);
			n->enemytimer = 0;
		}

		if (n->direction == RIGHT)
		{
			n->position.x += n->speed * tools::GetTimeDelta();
		}
		if (n->direction == LEFT)
		{
			n->position.x -= n->speed * tools::GetTimeDelta();
		}
		if (n->direction == DOWN)
		{
			n->position.y += n->speed * tools::GetTimeDelta();
		}
		if (n->direction == UP)
		{
			n->position.y -= n->speed * tools::GetTimeDelta();
		}
		if (tools::Circle_Collision(n->position, player->GetPos(), 20, 20))
		{ 
			player->death = true;
		}
	
		n->EnemyS.setPosition(n->position);
	}

	
	
}

void Enemy::DisplayEnemy(sf::RenderWindow& _window, sf::Shader* _shader)
{
	if (player->death == true)
	{
		ActivateDeathScreen(_window, player->death);
	}
	for (auto n : enemycontainer)
	{
		if (tools::Circle_Collision(n->position, player->GetPos(), 70, 70))
		{
			float fadeInTime = 0.5f;
			float holdTime = 0.5f;
			float fadeOutTime = 0.5f;
			float totalDuration = fadeInTime + holdTime + fadeOutTime;
			float opacity = 0;
			static float timeElapsed = 0.0f;
			timeElapsed += tools::GetTimeDelta();
			if (timeElapsed < fadeInTime) {
				opacity = timeElapsed / fadeInTime;
			}
			else if (timeElapsed < fadeInTime + holdTime) {
				sounds.playSound("alert");
				opacity = 1;
			}
			else if (timeElapsed < totalDuration) {
				opacity = 1 - (timeElapsed - fadeInTime - holdTime) / fadeOutTime;
			}
			else {
				timeElapsed = 0.0f;
			}
			WarningS.setColor(sf::Color(255, 255, 255, 255 * opacity));
			WarningS.setPosition(sf::Vector2f(player->GetPos().x - 10, player->GetPos().y - 30));
			_window.draw(WarningS);
		}
		_window.draw(n->EnemyS, _shader);
	}
	
}

void Enemy::DisplaySpeeches(sf::RenderWindow& _window, sf::Shader* shader)
{
	
	for (auto n : Speeches)
	{
		if (tools::Circle_Collision(player->GetPos(), sf::Vector2f(n->spritespeech.getGlobalBounds().left + n->spritespeech.getGlobalBounds().width/2, n->spritespeech.getGlobalBounds().top + n->spritespeech.getGlobalBounds().height/2), 25, 25))
		_window.draw(n->spritespeech);
	}
	
}
