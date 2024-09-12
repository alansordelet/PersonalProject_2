#pragma once
#include "tools.h"
#include "StateManager.h"
#include "SoundManager.h"




class Menu
{
public:
	Menu() {};
	
	Menu(stateManager* _state);
	void init();
	void update(sf::RenderWindow& _window, sf::Event& _event);
	void setFullscreen(sf::RenderWindow& _window);
	void setVsynch(sf::RenderWindow& _window);
	float soundAlgo(sf::Vector2f _x);
	void setSoundVolume(sf::RenderWindow& _window, sf::Event& _event);
	void updateOptions(sf::RenderWindow& _window, sf::Event& _event);
	void display(sf::RenderWindow& _window);
	void drawVolume(sf::RenderWindow& _window);
	void displayOptions(sf::RenderWindow& _window);

protected:
	float menuTimer;
private:
	stateManager* sm;
	SoundManager sounds;
	sf::View viewmenu;
	sf::RectangleShape menuToGameRs;
	bool playMusic = false;
	sf::RectangleShape menuToOptionsRs;
	sf::RectangleShape rs3;
	sf::RectangleShape rs4;

	sf::RectangleShape volumeBar;
	sf::CircleShape volumeButton;

	sf::Texture menuTexture;
	sf::Texture menuTexture2;

	sf::Vector2f menuPosition;

	sf::Text t;
	sf::Text tJouer;
	sf::Text tOption;
	sf::Font f;
	sf::Text text;
	sf::Font font;
	sf::Text text2;
	//Pour rentrer l'IP et le Port
	bool inEmptyMenu; //dans le menu de base
	bool choosingGame; //choix entre host et join
	bool hostingGame;//apres avoir choisi host
	bool joiningGame;//apres avoir choisi join
	bool optionactive = false;
	sf::RectangleShape cursorRS;
	bool showCursor;
			

	bool fullscreen;
	bool vsynch;


	bool isDragging;

	//POUR LE LOBBY

	bool hostConnected;
	bool clientConnected;
};
