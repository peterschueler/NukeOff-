#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.hpp"
#include "Level.hpp"

class Game : public sf::NonCopyable, public State {
public:
	explicit Game(sf::RenderWindow&);
	
	bool processInput(sf::Event&);
	bool update(sf::Time);
	void render();
	
private:
	void selectLevel(unsigned int);
	void nextLevel();
	void previousLevel();
	
	void setupLevels();
	
	sf::RenderWindow& window;
	sf::FloatRect bounds;
	
	Level* currentLevel;
	std::vector<Level> levels;
	bool gameOver;
};

#endif