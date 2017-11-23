#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>

class State {
public:
	virtual bool processInput(sf::Event&) = 0;
	virtual bool update(sf::Time) = 0;
	virtual void render() = 0;
};

#endif