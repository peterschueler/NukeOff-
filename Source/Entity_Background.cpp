#include "../Include/Entity_Background.hpp"
#include "../Include/TextureManager.hpp"

#include <iostream>

Entity_Background::Entity_Background() : sprite(), scaleX(320), scaleY(240) {
	attachTexture();
}

Entity_Background::Entity_Background(Tile tile, const std::shared_ptr<TextureManager>& mgr) : sprite(), txtManager(mgr), tile(tile), scaleX(320), scaleY(240) {
	attachTexture();
}

void Entity_Background::update(sf::Time delta) {
	move(direction * delta.asSeconds());
}

sf::FloatRect Entity_Background::borders() const {
	sf::FloatRect bounds = getTransform().transformRect(sprite.getGlobalBounds());
	return bounds;
}

void Entity_Background::setDirection(float vx, float vy) {
	direction.x = vx;
	direction.y = vy;
}

sf::Vector2f Entity_Background::getDirection() const {
	return direction;
}

void Entity_Background::setScale(int _x, int _y) {
	scaleX = _x;
	scaleY = _y;
	attachTexture();
}

void Entity_Background::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	
	target.draw(sprite, states);
}

void Entity_Background::attachTexture() {
	int x_axis = scaleX;
	int y_axis = scaleY;
	
	sf::IntRect rect = sf::IntRect(0,0,x_axis, y_axis);
	txtManager->load(tile.type);
	sf::Texture& texture = txtManager->get(tile.type);
	texture.setRepeated(true);
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
}