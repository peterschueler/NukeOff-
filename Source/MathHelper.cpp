#include "../Include/MathHelper.hpp"

#include <cmath>

sf::Vector2f omeMath::normalize2f(const sf::Vector2f aVector) {
	sf::Vector2f newVector(0,0);
	newVector.x = aVector.x / magnitude2f(aVector);
	newVector.y = aVector.y / magnitude2f(aVector);
	return newVector;
}

float omeMath::magnitude2f(const sf::Vector2f aVector) {
	return sqrt(aVector.x * 2 + aVector.y * 2);	
}

float omeMath::dotProduct2f(const sf::Vector2f aVector, const sf::Vector2f bVector) {
	float xComponent = aVector.x * bVector.x;
	float yComponent = aVector.y * bVector.y;
	return xComponent + yComponent;
}