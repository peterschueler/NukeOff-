#ifndef TextGame_hpp
#define TextGame_hpp

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.hpp"

#include "../Include/TextureManager.hpp"

class TextGame : public sf::NonCopyable, public State {
public:
	explicit TextGame(sf::RenderWindow&, sf::View&);
	
	bool processInput(sf::Event&);
	ExitState update(sf::Time);
	void render();
	
	void resetNuke();
	
private:
	sf::RenderWindow& window;
	sf::View& view;
	
	bool gameOver;
	bool gotNuked;
	
	std::shared_ptr<TextureManager> txtManager;
};

#endif