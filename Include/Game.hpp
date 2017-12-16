#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.hpp"
#include "Level.hpp"

class Entity_Brick;
class Entity_Wall;

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
	
	void initializeLevels();
	void setupLevel(unsigned int, Level*);
	
	sf::RenderWindow& window;
	sf::FloatRect bounds;
	
	Level* currentLevel;
	std::vector<Level*> levels;
	std::vector<Entity_Brick*> bricks;
	std::vector<Entity_Wall*> walls;
	bool gameOver;
};

#endif