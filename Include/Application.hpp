#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "State.hpp"
#include "Menu.hpp"
#include "Game.hpp"
#include "JumpGame.hpp"

class Application {
public:
	Application();
	void run();
	
private:
	void processInput();
	void update(sf::Time delta);
	void render();
	
private:
	sf::RenderWindow window;
	sf::View view;
	static const sf::Time secondsFramesRatio;
	
	State* currentState;
	Menu menuState;
	Game gameState;
};

#endif