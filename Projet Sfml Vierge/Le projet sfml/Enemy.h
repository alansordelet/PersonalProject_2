#pragma once
#include"tools.h"
#include"Player.h"
#include"SoundManager.h"

class MySpeeches
{
public:
	MySpeeches(sf::Vector2f _pos, std::string _speechnb, sf::Vector2f _size)
	{
		texturespeech.loadFromFile("..\\Ressources\\Textures\\" + _speechnb);
		spritespeech.setTexture(texturespeech);
		spritespeech.setPosition(_pos); 
		spritespeech.setScale(_size);
	};
	MySpeeches() {};
	~MySpeeches() {};
	sf::Texture texturespeech;
	sf::Sprite spritespeech;
private:

};

enum Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Enemy
{
public :
	Enemy(Player* _player);
		
	Enemy() {};
	Enemy(sf::Vector2f _pos, Direction _firstdirection, bool _reverse);
	~Enemy() {};
	void ActivateDeathScreen(sf::RenderWindow& _window, bool _thisbool);
	void firstMaze();
	void LoopdyLoop();
	void secondMaze();
	void UpdateEnemy();
	void DisplayEnemy(sf::RenderWindow& _window, sf::Shader* _shader);
	void DisplaySpeeches(sf::RenderWindow& _window, sf::Shader* shader);
	std::vector<Enemy*> enemycontainer;
	
private :
	bool playMusic = false;
	SoundManager sounds;
	float timerspawnthem = 0;
	int howmany = 0;
	sf::Vector2f positionRespawn = { 0,0 };
	float speed;
	sf::Vector2f position;
	sf::Sprite EnemyS;
	sf::Sprite WarningS;
	sf::Texture EnemyT;
	sf::Texture WarningT;
	sf::IntRect enemyRect;
	float enemytimer = 0;
	float spawntimer = 0;
	int frameX = 0;
	int frameY = 0;
	bool reverseSecond = false;
	bool reverseLoop = false;
	Direction direction;
	Player* player;
	std::vector<MySpeeches*> Speeches;
	bool firstspawn = false;
	bool secondspawn = false;
	bool gethit = false;
	sf::RectangleShape blackScreen;
	float alpha = 0.0f;
	bool fadeOut = false;
	bool gottimenoise = false;
	bool gotbooknoise = false;
};

