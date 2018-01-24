#include "../Include/Entity_Paddle.hpp"

#include <iostream>

Entity_Paddle::Entity_Paddle() : sprite(), texture(), tile() {
	tile.type = Tile::Type::Paddle_Short;
	attachTexture();
}

Entity_Paddle::Entity_Paddle(Tile tl, const std::shared_ptr<TextureManager>& mgr): sprite(), texture(), tile(tl), txtManager(mgr) {
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
	if (tile.type == Tile::Type::Paddle_Long) {
		float y_axis = y - 20;
		setPosition(x, y_axis);
		return;
	}
	setPosition(x, y);
}

sf::Vector2f Entity_Paddle::getAdjustedPosition() const {
	if (tile.type == Tile::Type::Paddle_Long) {
		float y_axis = getPosition().y + 20;
		sf::Vector2f adjustedPosition = sf::Vector2f(getPosition().x, y_axis);
		return adjustedPosition;
	}
	return getPosition();
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
	int y_axis = 0;
	if (tile.type == Tile::Type::Paddle_Short) {
		y_axis = 20;
	} else if (tile.type == Tile::Type::Paddle_Long) {
		y_axis = 40;
	}
	
	sf::IntRect rect = sf::IntRect(0,0,10,y_axis);
	txtManager->load(tile.type);
	sprite.setTexture(txtManager->get(tile.type));
	sprite.setTextureRect(rect);
}