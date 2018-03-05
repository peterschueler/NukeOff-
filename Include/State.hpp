#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>

enum class ExitState {
	GameOver,
	Nuked,
	Running,
};

class State {
public:
	virtual bool processInput(sf::Event&) = 0;
	virtual ExitState update(sf::Time) = 0;
	virtual void render() = 0;
	virtual void resetNuke() = 0;
};

#endif