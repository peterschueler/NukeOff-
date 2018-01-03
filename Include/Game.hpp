#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.hpp"
#include "Level.hpp"

class Entity_Brick;
class Entity_Wall;
class Entity_Paddle;
class Entity_Ball;

class TextureManager;

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
	
	void checkCollisions();
	
	sf::RenderWindow& window;
	sf::FloatRect bounds;
	
	Level* currentLevel;
	std::vector<Level*> levels;
	std::vector<Entity_Brick*> bricks;
	std::vector<Entity_Wall*> walls;
	Entity_Paddle* paddle;
	Entity_Ball* ball;
	bool gameOver;
	
	float upperBorder;
	float lowerBorder;
	
	TextureManager* txtManager;
};

#endif