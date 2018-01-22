#include "../Include/Entity_Paddle.hpp"

#include <iostream>

Entity_Paddle::Entity_Paddle() : sprite(), texture(), state(Entity_Paddle::Paddle_State::Short) {
	attachTexture();
}

void Entity_Paddle::update(sf::Time delta) {
	move(direction * delta.asSeconds());
}

sf::FloatRect Entity_Paddle::borders() const {
	sf::FloatRect bounds = getTransform().transformRect(sprite.getGlobalBounds());
	return bounds;
}

void Entity_Paddle::setAdjustedPosition(float x, float y) {
	if (state == Entity_Paddle::Paddle_State::Long) {
		float y_axis = y - 20;
		setPosition(x, y_axis);
		return;
	}
	setPosition(x, y);
}

sf::Vector2f Entity_Paddle::getAdjustedPosition() const {
	if (state == Entity_Paddle::Paddle_State::Long) {
		float y_axis = getPosition().y + 20;
		sf::Vector2f adjustedPosition = sf::Vector2f(getPosition().x, y_axis);
		return adjustedPosition;
	}
	return getPosition();
}

void Entity_Paddle::setState(Entity_Paddle::Paddle_State st) {
	state = st;
	attachTexture();
}

void Entity_Paddle::moveUp(float vy) {
	direction.y = vy;
}

void Entity_Paddle::stop() {
	direction.y = 0;
}

void Entity_Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	
	target.draw(sprite, states);
}

void Entity_Paddle::attachTexture() {
	std::string filePath = "Assets/Textures/Objects/Default/Paddle";
	int y_axis = 0;
	if (state == Entity_Paddle::Paddle_State::Short) {
		filePath = filePath + "_Small.png";
		y_axis = 20;
	} else if (state == Entity_Paddle::Paddle_State::Long){
		filePath = filePath + "_Large.png";
		std::cout << "It's long now." << std::endl;
		y_axis = 40;
	}
	
	sf::IntRect rect = sf::IntRect(0,0,10,y_axis);
	if (texture.loadFromFile(filePath)) {
		sprite.setTexture(texture);
		sprite.setTextureRect(rect);
	} else {
		std::cerr << "Couldn't load " << filePath << ". Did you misplace the the texture file?" << std::endl;
	}
}