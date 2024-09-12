#include "Maps.h"

std::vector<structMap> Maps::layer1;
std::vector<structMap> Maps::layer2;
std::vector<structMap> Maps::layer3;

Maps::Maps()
{
	textureMap.loadFromFile("..\\Ressources\\Textures\\ground.png");
	textureMap2.loadFromFile("..\\Ressources\\Textures\\Tileset_Large.png");
	HitboxT.loadFromFile("..\\Ressources\\Textures\\Untitled.png");
	SpellT.loadFromFile("..\\Ressources\\Textures\\spell.png");
	SpellS.setTexture(SpellT); 
	doorT.loadFromFile("..\\Ressources\\Textures\\door.png");
	doorS.setTexture(doorT);
	clockT.loadFromFile("..\\Ressources\\Textures\\clock.png");
	clockS.setTexture(clockT);
	cloakT.loadFromFile("..\\Ressources\\Textures\\cloak.png");
	cloakS.setTexture(cloakT);
	SpellS.setPosition(820.0f, 800.f);
	clockS.setPosition(820.0f, 800.f);
	cloakS.setPosition(700, 700);
	doorS.setPosition(700, 700);
	SpellS.setScale(sf::Vector2f(0.5,0.5));
	clockS.setScale(sf::Vector2f(0.1,0.1));
	cloakS.setScale(sf::Vector2f(0.1,0.1));
	HitboxS.setTexture(HitboxT);
	HitboxS.setTextureRect(SolRect);
	font.loadFromFile("..\\Ressources\\bloody.ttf");
	spriteMap.setTexture(textureMap);
	spriteMap2.setTexture(textureMap2);
	QuickLoad();
	viewGame.setCenter(0, 0);
	viewGame.setSize(Vector2f(600, 400));
	viewHUD.setSize(Vector2f(1920, 1080));
	layerNumber = FIRST;
	tileSelec = 1;
	timerEdit = 0;
	layerSelec = 1;
	texts.push_back(new MyTexts(sf::Vector2f(85, 60), "Welcome...", 10));
	texts.push_back(new MyTexts(sf::Vector2f(530, 160), "Good Luck...", 14));
	texts.push_back(new MyTexts(sf::Vector2f(450, 565), "THE TWINS", 10));
	for (size_t i = 0; i < 14; i++)
	{
		texts.push_back(new MyTexts(sf::Vector2f(280 + (i * 55), 847), "I SEE YOU", 8));
	}
	flashlights.push_back(new MyFlashlights(sf::Vector2f(311, 220)));
	flashlights.push_back(new MyFlashlights(sf::Vector2f(509, 54)));
	flashlights.push_back(new MyFlashlights(sf::Vector2f(859, 170)));
	flashlights.push_back(new MyFlashlights(sf::Vector2f(141, 960)));
}

Maps::~Maps()
{

}

void Maps::UpdateMaps(RenderWindow& _window)
{
	sf::Vector2i mouse = sf::Mouse::getPosition(_window);
	sf::Vector2f _mousePixel = _window.mapPixelToCoords(mouse, _window.getView());
	std::cout << _mousePixel.x << " " << _mousePixel.y << std::endl;
	_mousePixel.x = ((int)_mousePixel.x / 16);
	_mousePixel.x *= 16;
	_mousePixel.y = ((int)_mousePixel.y / 16);
	_mousePixel.y *= 16;
	int i = -1;
	int layerTmp = layerNumber;
	timerEdit += tools::GetTimeDelta();
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && timerEdit > 0.5)
	{
		if (layerNumber < COLLISION)
		{
			layerTmp++;
			layerSelec++;
			layerNumber = (layer)layerTmp;
		}
		else //si on est à la couche max revient à 0
		{
			layerSelec = 1;
			layerNumber = FIRST;
		}
		std::cout << layerNumber << std::endl;
		timerEdit = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && timerEdit > 0.5)
	{
		if (layerNumber > FIRST)
		{
			layerTmp--;
			layerSelec--;
			layerNumber = (layer)layerTmp;
		}
		else//si on est à la couche min revient à la couche max
		{
			layerSelec = 3;
			layerNumber = COLLISION;
		}
		std::cout << layerNumber << std::endl;
		timerEdit = 0;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timerEdit > 0.2) //clique gauche pour posé les tiles
	{
		switch (layerNumber)//pose en fonction du numéro de la couche
		{
		case FIRST:
			for (structMap _o : layer1) {
				i++;
				if (_mousePixel.x == _o.position.x && _mousePixel.y == _o.position.y)
					break;
			}
			layer1[i].tile = tileSelec;
			break;
		case SECOND:
			for (structMap _o : layer2) {
				i++;
				if (_mousePixel.x == _o.position.x && _mousePixel.y == _o.position.y)
					break;
			}
			layer2[i].tile = tileSelec;
			break;
		case COLLISION:
			for (structMap _o : layer3) {
				i++;
				if (_mousePixel.x == _o.position.x && _mousePixel.y == _o.position.y)
					break;
			}
			layer3[i].tile = tileSelec;
			break;
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && timerEdit > 0.2)//clique 3 pour copié une tile déjà posé sur la couche actuelle
	{
		switch (layerNumber) {
		case FIRST:
			for (structMap _o : layer1) {
				i++;
				if (_mousePixel.x == _o.position.x && _mousePixel.y == _o.position.y)
					break;
			}
			tileSelec = layer1[i].tile;
			break;
		case SECOND:
			for (structMap _o : layer2) {
				i++;
				if (_mousePixel.x == _o.position.x && _mousePixel.y == _o.position.y)
					break;
			}
			tileSelec = layer2[i].tile;
			break;
		case COLLISION:
			for (structMap _o : layer3) {
				i++;
				if (_mousePixel.x == _o.position.x && _mousePixel.y == _o.position.y)
					break;
			}
			tileSelec = layer3[i].tile;
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && tileSelec > 0 && timerEdit > 0.1)
	{
		tileSelec--;
		timerEdit = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && tileSelec < 350 && timerEdit > 0.1)
	{
		tileSelec++;
		timerEdit = 0;
	}
	
}

void Maps::DrawMapTile(sf::RenderWindow& _window)
{
	sf::IntRect tmpRect{ 0,0,16,16 };
	sf::Vector2i mousePosi = sf::Mouse::getPosition(_window);
	Vector2f mousePixel = _window.mapPixelToCoords(mousePosi);
	sf::Sprite drawMouseTile;
	mousePixel.x = (int)(mousePixel.x / 16);
	mousePixel.y = (int)(mousePixel.y / 16);
	mousePixel.x *= 16;
	mousePixel.y *= 16;

	tmpRect.left = (tileSelec % 16) * 16;
	tmpRect.top = (tileSelec / 16) * 16;
	tmpRect.width = 16;
	tmpRect.height = 16;
	if (layerSelec == 1)
		drawMouseTile.setTexture(textureMap);
	else if (layerSelec == 2)
		drawMouseTile.setTexture(textureMap2);
	else if (layerSelec == 3)
		drawMouseTile.setTexture(HitboxT);
	drawMouseTile.setTextureRect(tmpRect);
	drawMouseTile.setPosition(mousePixel);
	drawMouseTile.setColor(Color::White);

	_window.draw(drawMouseTile);
}



void Maps::DisplayMaps(RenderWindow& _window, sf::Shader* shader)
{
	if(stateManager::state == enumState::EDITOR)
	DrawMapTile(_window);
	timeanimation += 20 * tools::GetTimeDelta();
	if (gotSpell == false)
	{
		float posY = initialY + amplitude * std::sin(timeanimation * frequency);
		SpellS.setPosition(820.0f, posY);
		_window.draw(SpellS);
	}

	if (gotTime == false)
	{
		float posY = initialY2 + amplitude * std::sin(timeanimation * frequency);
		clockS.setPosition(40, posY);
		
		_window.draw(clockS);
	}

	if (gotCloak == false)
	{
		float posY = initialY3 + amplitude * std::sin(timeanimation * frequency);
		cloakS.setPosition(300, posY);
		_window.draw(cloakS);
	}

	for (auto n : texts)
	{
		_window.draw(n->text, shader);
	}
	for (auto n : flashlights)
	{
		n->DisplayFlashlights(_window);
	}
	doorS.setPosition(730, 1538);
	_window.draw(doorS);
}



void Maps::QuickSave()
{
	std::ofstream fichierSave("..\\Ressources\\save\\1stLayer");
	int i = -1;
	for (structMap _o : layer1) {
		i++;
		if (i == 75)
		{
			i = 0;
			fichierSave << std::endl;
		}
		fichierSave << std::setw(4) << _o.tile;
	}

	std::ofstream fichierSave2("..\\Ressources\\save\\2ndLayer");
	i = -1;
	for (structMap _o : layer2) {
		i++;
		if (i == 75)
		{
			i = 0;
			fichierSave2 << std::endl;
		}
		fichierSave2 << std::setw(4) << _o.tile;
	}

	std::ofstream fichierSave3("..\\Ressources\\save\\3rdLayer");
	i = -1;
	for (structMap _o : layer3) {
		i++;
		if (i == 75)
		{
			i = 0;
			fichierSave3 << std::endl;
		}
		fichierSave3 << std::setw(4) << _o.tile;
	}
}

void Maps::QuickLoad()
{
	std::ifstream fichierLayer1("..\\Ressources\\save\\1stLayer");
	int i = -1;
	structMap tmpStruct{ sf::Vector2f(0.0f,0.0f),0 };
	while (!fichierLayer1.eof())
	{
		i++;
		fichierLayer1 >> tmpStruct.tile;
		layer1.push_back(tmpStruct);
		tmpStruct.position.x += 16;
		if (i == 75)
		{
			i = 0;
			tmpStruct.position.x = 0;
			tmpStruct.position.y += 16;
		}
	}
	fichierLayer1.close();

	std::ifstream fichierLayer2("..\\ressources\\save\\2ndLayer");
	i = -1;
	structMap tmpStruct2{ sf::Vector2f(0.0f,0.0f),0 };
	while (!fichierLayer2.eof())
	{
		i++;
		fichierLayer2 >> tmpStruct2.tile;
		layer2.push_back(tmpStruct2);
		tmpStruct2.position.x += 16;
		if (i == 75)
		{
			i = 0;
			tmpStruct2.position.x = 0;
			tmpStruct2.position.y += 16;
		}
	}
	fichierLayer2.close();

	std::ifstream fichierLayer3("..\\ressources\\save\\3rdLayer");
	i = -1;
	structMap tmpStruct3{ sf::Vector2f(0.0f,0.0f),0 };
	while (!fichierLayer3.eof())
	{
		i++;
		fichierLayer3 >> tmpStruct3.tile;
		layer3.push_back(tmpStruct3);
		tmpStruct3.position.x += 16;
		if (i == 75)
		{
			i = 0;
			tmpStruct3.position.x = 0;
			tmpStruct3.position.y += 16;
		}
	}
	fichierLayer3.close();
}

void Maps::zoom(Event event)
{
	if (stateManager::state == enumState::EDITOR)
	{
		float viewZoom = 1;

		if (event.type == sf::Event::MouseWheelMoved)
		{
			if (event.mouseWheelScroll.wheel > 0)
			{
				viewZoom -= 0.1;
			}
			if (event.mouseWheelScroll.wheel < 0)
			{
				viewZoom += 0.1;
			}
			viewGame.zoom(viewZoom);
		}
	}
	
}
