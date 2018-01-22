#ifndef MathHelper_hpp
#define MathHelper_hpp

#include <SFML/Graphics.hpp>

namespace omeMath {
	sf::Vector2f normalize2f(const sf::Vector2f);
	float magnitude2f(const sf::Vector2f);
	float dotProduct2f(const sf::Vector2f, const sf::Vector2f);
};

#endif