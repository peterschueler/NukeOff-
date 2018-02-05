#include "../Include/Entity_Ball.hpp"
#include "../Include/TextureManager.hpp"

#include <iostream>

Entity_Ball::Entity_Ball() : sprite(7.5) {
	tile.x = 0;
	tile.y = 0;
	tile.type = Tile::Type::Ball_Default;
	attachTexture();
	sprite.setOrigin(sprite.getRadius(), sprite.getRadius());
	txtManager = std::make_shared<TextureManager>();
}

Entity_Ball::Entity_Ball(Tile tile, const std::shared_ptr<TextureManager>& mgr): sprite(7.5), tile(tile), txtManager(mgr), speed(1) {
	attachTexture();
	sprite.setOrigin(sprite.getRadius(), sprite.getRadius());
}

void Entity_Ball::update(sf::Time delta) {
	rotate(-180 * delta.asSeconds());
	move(direction * speed * delta.asSeconds());
}

void Entity_Ball::setDirection(float vx, float vy) {
	direction.x = vx;
	direction.y = vy;
}

sf::Vector2f Entity_Ball::getDirection() const {
	return direction;
}

void Entity_Ball::setSpeed(float sp) {
	speed = sp;
}

sf::FloatRect Entity_Ball::borders() const {
	sf::FloatRect bounds = getTransform().transformRect(sprite.getGlobalBounds());
	return bounds;
}

sf::Vector2f Entity_Ball::getCenter() const {
	auto xCenter = borders().width / 2;
	auto yCenter = borders().height / 2;
	return sf::Vector2f(xCenter, yCenter);
}

void Entity_Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	
	target.draw(sprite, states);
}

void Entity_Ball::attachTexture() {
	int y_axis = 15;
	int x_axis = 15;
	
	sf::IntRect rect = sf::IntRect(0,0,x_axis, y_axis);
	txtManager->load(tile.type);
	sprite.setTexture(&txtManager->get(tile.type));
	sprite.setTextureRect(rect);
}