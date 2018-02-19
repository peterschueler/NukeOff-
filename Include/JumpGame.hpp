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

	sf::RenderWindow& window;
	sf::View& view;
	sf::FloatRect bounds;
	
	std::unique_ptr<Entity_Ball> character;
	
	std::shared_ptr<TextureManager> txtManager;
	
	bool gameOver;
};

#endif