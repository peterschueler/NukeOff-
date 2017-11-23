#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.hpp"

typedef unsigned int Level;

class Game : public sf::NonCopyable, public State {
public:
	explicit Game(sf::RenderWindow&);
	
	bool processInput(sf::Event&);
	bool update(sf::Time);
	void render();
	
private:
	sf::RenderWindow& window;
	sf::FloatRect bounds;
	
	Level currentLevel;
	bool gameOver;
};

#endif