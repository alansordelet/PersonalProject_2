#pragma once
#include"tools.h"
#include"Maps.h"
enum DirectionPlayer { DOWNS, LEFTS, RIGHTS, UPS, IDLES };

class Player
{
public :
	Player(Maps* _map);
	~Player();

	void update();
	void Display(RenderWindow& _window, sf::Shader* shader);
	inline Vector2f GetPos() { return pos; }
	inline void setPos(sf::Vector2f _newpos) { pos = _newpos; }
	void ViewManager(Player& _player, sf::RenderWindow& _window, stateManager& _state);
    bool collisionMapPlayer(FloatRect _MaleSprite, DirectionPlayer _direction, Vector2f _vitesse, int _tilenb, int _tilenb2, int _tilenb3, int _tilenb4);
	bool death = false;
	void DisplayMap(sf::RenderWindow& _window, sf::Shader* shader);
	void DisplayHUD(sf::RenderWindow& _window);
	int frameXH;
	Sprite spritePlayer;
	int tilenb = 0;
	int tilenb2 = 0;
	int tilenb3 = 0;
	bool thirdspawn = false;
	Maps* map;
	float BigTimer = 300;
private:
	Vector2f pos;
	sf::Texture texturePlayer;
	sf::Texture textureHearts;
	sf::Texture textureDeath;
	sf::Texture texturePlank;
	int secondsRemaining= 0;
	Sprite spritePlank;
	Sprite spriteHearts;
	sf::Vector2f speed;
	IntRect rectPlayer;
	IntRect rectHearts = {0,0,16,16};
	int frameX;
	int frameY;
	float timerPlayer;
	bool isMoving;
	Vector2i MaleSprite;
	Vector2i MaleSprite2;
	Vector2i MaleSprite3;
	Vector2i MaleSprite4;
	sf::ConvexShape beam;
	DirectionPlayer directionu;
	float LightIncrease = 3.0;

	float countdownTimer = 0;
    sf::Font font;
};

