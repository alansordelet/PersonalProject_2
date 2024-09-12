#pragma once
#include"tools.h"
#include <fstream>
#include <iomanip>
#include "stateManager.h"

class MyFlashlights
{
public:
	MyFlashlights(sf::Vector2f _pos)
	{
		flashlightT.loadFromFile("..\\Ressources\\Textures\\flashlight.png");
		flashlightS.setTexture(flashlightT);
		pos = _pos;
		initialY = _pos.y;
		flashlightS.setPosition(pos);
		flashlightS.setScale(sf::Vector2f(0.2,0.2));
	};
	MyFlashlights() {};
	~MyFlashlights() {};
	void DisplayFlashlights(sf::RenderWindow& _window)
	{
		timeanimation += 20 * tools::GetTimeDelta();
		float posY = initialY + amplitude * std::sin(timeanimation * frequency);
		flashlightS.setPosition(pos.x, posY);
		_window.draw(flashlightS);
	};
	sf::Texture flashlightT;
	sf::Sprite flashlightS;
private:
	float initialY = 0.0f;
	float amplitude = 10.0f;
	float frequency = 0.2f;
	float timeanimation = 0.0f;
	sf::Vector2f pos;
};

class MyTexts
{
public:
	MyTexts(sf::Vector2f _pos, sf::String _sentence, float size)
	{
		font.loadFromFile("..\\Ressources\\bloody.ttf");
		text.setFont(font);
		text.setFillColor(sf::Color::Red);
		text.setPosition(_pos);
		text.setString(_sentence);
		text.setCharacterSize(size);
	};
	MyTexts() {};
	~MyTexts() {};
	sf::Text text;
private:
	
	sf::Font font;
};

struct structMap {
	sf::Vector2f position;
	int tile;
};

enum layer {
	FIRST = 1, SECOND, COLLISION
};

class Maps
{
public :
	Maps();
	~Maps();

	void UpdateMaps(sf::RenderWindow& _window);
	void DrawMapTile(sf::RenderWindow& _window);
	
	void DisplayMaps(sf::RenderWindow& _window, sf::Shader* shader);
	inline void setViewHUD(sf::RenderWindow& _window)
	{
		_window.setView(viewHUD);
		sf::Text textlayer;
		textlayer.setFont(font);
		textlayer.setString("Layer :" + std::to_string(layerNumber));
		if (stateManager::state == enumState::EDITOR)
		_window.draw(textlayer);
	};
	void QuickSave();
	void QuickLoad();
	void zoom(Event event);


	View viewGame;
	View viewHUD;
	Sprite spriteMap;
	Sprite spriteMap2;
	Vector2f posView;
	static std::vector<structMap> layer1;
	static std::vector<structMap> layer2;
	static std::vector<structMap> layer3;
	Sprite HitboxS;
	IntRect SolRect = { 0,0,16,16 };
	Sprite SpellS;
	Sprite clockS;
	Sprite cloakS;
	Sprite doorS;
	std::vector<MyFlashlights*> flashlights;
	bool gotSpell = false;
	bool gotTime = false;
	bool gotCloak = false;
private :

	Texture HitboxT;
	Texture SpellT;
	Texture clockT;
	Texture cloakT;
	Texture doorT;
	
	layer layerNumber;
	int tileSelec;
	int layerSelec;
	float timerEdit;
	std::vector<MyTexts*> texts;

	Texture textureMap;
	Texture textureMap2;
	sf::Font font;
	
	float initialY = 70.0f;
	float initialY2 = 380.0f;
	float initialY3 = 700.0f;
	float amplitude = 10.0f;
	float frequency = 0.2f;
	float timeanimation = 0.0f;
};

