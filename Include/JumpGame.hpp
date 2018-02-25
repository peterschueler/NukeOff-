#ifndef JumpGame_hpp
#define JumpGame_hpp

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.hpp"

#include "Entity_Brick.hpp"
#include "Entity_Wall.hpp"
#include "Entity_Ball.hpp"
#include "TextureManager.hpp"

class JumpGame : public sf::NonCopyable, public State {
public:
	explicit JumpGame(sf::RenderWindow&, sf::View&);
	
	bool processInput(sf::Event&);
	bool update(sf::Time);
	void render();
	
private:
	// There's only a single level. It's an interlude, not a full-on game.
	void buildLevel();
	void checkCollision();

	sf::RenderWindow& window;
	sf::View& view;
	sf::FloatRect bounds;
	
	float elapsedProjectileTime;
	
	std::unique_ptr<Entity_Ball> character;
	std::vector<std::shared_ptr<Entity_Wall> > walls;
	std::vector<std::shared_ptr<Entity_Brick> > projectiles;
	
	std::shared_ptr<TextureManager> txtManager;
	
	bool gameOver;
};

#endif