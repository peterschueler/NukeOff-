#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.hpp"
#include "Tile.hpp"
#include "Level.hpp"

#include "../Include/Entity_Brick.hpp"
#include "../Include/Entity_Wall.hpp"
#include "../Include/Entity_Paddle.hpp"
#include "../Include/Entity_Ball.hpp"
#include "../Include/Entity_Background.hpp"
#include "../Include/TextureManager.hpp"

class Game : public sf::NonCopyable, public State {
public:
	explicit Game(sf::RenderWindow&, sf::View&);
	
	bool processInput(sf::Event&);
	ExitState update(sf::Time);
	void render();
	void resetNuke() { gotNuked = false; };
	
private:
	void selectLevel(unsigned int);
	void nextLevel();
	void previousLevel();
	
	void initializeLevels();
	void setupLevel(unsigned int, std::shared_ptr<Level>);
	void resetLevel(unsigned int);
	
	void checkCollisions();
	
	void testFunc();
	
	sf::RenderWindow& window;
	sf::View& view;
	sf::FloatRect bounds;
	
	std::shared_ptr<Level> currentLevel;
	std::vector<std::shared_ptr<Level>> levels;
	std::vector<std::shared_ptr<Entity_Brick>> bricks;
	std::vector<std::shared_ptr<Entity_Wall>> walls;
	std::unique_ptr<Entity_Paddle> paddle;
	std::unique_ptr<Entity_Ball> ball;
	std::unique_ptr<Entity_Background> currentBackground;

	bool gameOver;
	bool gotNuked;
	unsigned int points;
	
	float upperBorder;
	float lowerBorder;
	
	float ballSpeedScale;
	
	std::shared_ptr<TextureManager> txtManager;
};

#endif