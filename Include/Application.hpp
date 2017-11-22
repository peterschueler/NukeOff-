#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

class Application {
public:
	Application();
	void run();
	
private:
	void processInput();
	void update(sf::Time delta);
	void render();
	
private:
	sf::RenderWindow window;
	static const sf::Time secondsFramesRatio;
};

#endif