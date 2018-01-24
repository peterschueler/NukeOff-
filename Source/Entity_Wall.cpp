#include "../Include/Entity_Wall.hpp"
#include "../Include/TextureManager.hpp"

#include <iostream>

Entity_Wall::Entity_Wall(Tile wl, unsigned int lvl, TextureManager& mgr) : sprite(), tile(wl), level(lvl), txtManager(&mgr) {
	setPosition(wl.x, wl.y);
	attachTexture();
}

Entity_Wall::Entity_Wall(int x, int y, int rot, Tile::Type ty, unsigned int lvl, TextureManager& mgr) : sprite(), tile(x,y,rot, ty), level(lvl), txtManager(&mgr) {
	setPosition(x, y);
	attachTexture();
}

void Entity_Wall::update(sf::Time time) {
}

sf::FloatRect Entity_Wall::borders() const {
	sf::FloatRect bounds = getTransform().transformRect(sprite.getGlobalBounds());
	return bounds;
}

sf::Vector2f Entity_Wall::getCenter() const {
	auto xCenter = borders().width / 2;
	auto yCenter = borders().height / 2;
	return sf::Vector2f(xCenter, yCenter);
}

void Entity_Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	
	target.draw(sprite, states);
}

void Entity_Wall::attachTexture() {
	int x = 0;
	int y = 20;
	if (tile.type == Tile::Type::Wall_Long_Yellow) {
		x = 60;
	} else if (tile.type == Tile::Type::Wall_Medium_Yellow) {
		x = 30;
	} else if (tile.type == Tile::Type::Wall_Short_Yellow) {
		x = 20;
	} else if (tile.type == Tile::Type::Wall_Corner_Yellow) {
		x = 20;
		y = 20;
	}
	sprite.setOrigin(sprite.getGlobalBounds().height / 2, sprite.getGlobalBounds().width / 2);
	sf::IntRect rect = sf::IntRect(0,0,x,y);
	sprite.setRotation(tile.rotation);
	txtManager->load(tile.type);
	sprite.setTexture(txtManager->get(tile.type));
	sprite.setTextureRect(rect);
}