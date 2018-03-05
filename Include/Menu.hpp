#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.hpp"

class Menu : public sf::NonCopyable, public State {
public:
	explicit Menu(sf::RenderWindow&);
	
	bool processInput(sf::Event&);
	ExitState update(sf::Time);
	void render();
	void resetNuke() {};
	
private:
	sf::RenderWindow& window;
	sf::FloatRect bounds;
};

#endif