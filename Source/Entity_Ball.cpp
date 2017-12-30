#include "../Include/Entity_Ball.hpp"

#include <iostream>

Entity_Ball::Entity_Ball() : sprite(7.5), texture() {
	attachTexture();
	setOrigin(borders().width / 2, borders().height / 2);
}

void Entity_Ball::update(sf::Time delta) {
	rotate(-180 * delta.asSeconds());
	move(direction * delta.asSeconds());
}

void Entity_Ball::setDirection(float vx, float vy) {
	direction.x = vx;
	direction.y = vy;
}

sf::Vector2f Entity_Ball::getDirection() const {
	return direction;
}

sf::FloatRect Entity_Ball::borders() const {
	sf::FloatRect bounds = getTransform().transformRect(sprite.getGlobalBounds());
	return bounds;
}

void Entity_Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	
	target.draw(sprite, states);
}

void Entity_Ball::attachTexture() {
	std::string filePath = "Assets/Textures/Objects/Default/Ball.png";
	int y_axis = 15;
	int x_axis = 15;

	sf::IntRect rect = sf::IntRect(0,0,x_axis, y_axis);
	if (texture.loadFromFile(filePath)) {
		sprite.setTexture(&texture);
		sprite.setTextureRect(rect);
	} else {
		std::cerr << "Couldn't load " << filePath << ". Did you misplace the the texture file?" << std::endl;
	}
	std::cout << "x: " << sprite.getGlobalBounds().width << " y: " << sprite.getGlobalBounds().height << std::endl;
}