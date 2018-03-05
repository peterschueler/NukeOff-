#ifndef JumpGame_hpp
#define JumpGame_hpp

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.hpp"

#include "Entity_Brick.hpp"
#include "Entity_Wall.hpp"
#include "Entity_Ball.hpp"
#include "Entity_Paddle.hpp"
#include "Entity_Background.hpp"
#include "TextureManager.hpp"

class JumpGame : public sf::NonCopyable, public State {
public:
	explicit JumpGame(sf::RenderWindow&, sf::View&);
	
	bool processInput(sf::Event&);
	ExitState update(sf::Time);
	void render();
	void resetNuke() { gotNuked = false; };
	
private:
	// There's only a single level. It's an interlude, not a full-on game.
	void buildLevel();
	void checkCollision();
	void flipMirrorPaddle();
	void fireProjectile(sf::Time);
	// Every time a brick hits the floor, the world becomes less stable.
	void increaseCorruption(std::shared_ptr<Entity_Brick>);

	sf::RenderWindow& window;
	sf::View& view;
	sf::FloatRect bounds;
	
	float elapsedProjectileTime;
	unsigned int corruption;
	
	std::unique_ptr<Entity_Ball> character;
	std::unique_ptr<Entity_Paddle> mirrorPaddle;
	std::vector<std::shared_ptr<Entity_Wall> > walls;
	std::vector<std::shared_ptr<Entity_Wall> > topWalls;
	std::vector<std::shared_ptr<Entity_Brick> > projectiles;
	std::unique_ptr<Entity_Background> currentBackground;
	
	std::shared_ptr<TextureManager> txtManager;
	
	bool gameOver;
	bool gotNuked;
};

#endif