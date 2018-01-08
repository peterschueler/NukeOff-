#include "../Include/Entity_Wall.hpp"
#include "../Include/TextureManager.hpp"

#include <iostream>

Entity_Wall::Entity_Wall() : sprite(), level(0) {
	attachTexture();
	txtManager = new TextureManager();
}

Entity_Wall::Entity_Wall(Tile wl, unsigned int lvl, TextureManager& mgr) : sprite(), tile(wl), level(lvl), txtManager(&mgr) {
	attachTexture();
	setPosition(wl.x, wl.y);
}

Entity_Wall::Entity_Wall(int x, int y, int rot, Tile::Type ty, unsigned int lvl) : sprite(), tile(x,y,rot, ty), level(lvl) {
	attachTexture();
	setPosition(x, y);
}

void Entity_Wall::update(sf::Time time) {
}

sf::FloatRect Entity_Wall::borders() const {
	sf::FloatRect bounds = getTransform().transformRect(sprite.getGlobalBounds());
	return bounds;
}

void Entity_Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	
	target.draw(sprite, states);
}

void Entity_Wall::attachTexture() {
	std::string filePath = "Assets/Textures/Walls/" + std::to_string(level) + "/Wall_";
	int x = 0;
	int y = 20;
	if (tile.type == Tile::Type::Wall_Long_Yellow) {
		filePath = filePath + "Long.png";
		x = 60;
	} else if (tile.type == Tile::Type::Wall_Medium_Yellow) {
		filePath = filePath + "Medium.png";
		x = 30;
	} else if (tile.type == Tile::Type::Wall_Short_Yellow) {
		filePath = filePath + "Short.png";	
		x = 20;
	} else if (tile.type == Tile::Type::Wall_Corner_Yellow) {
		filePath = filePath + "Corner.png";
		x = 20;
		y = 20;
	}
	sprite.setOrigin(sprite.getGlobalBounds().height / 2, sprite.getGlobalBounds().width / 2);
	sf::IntRect rect = sf::IntRect(0,0,x,y);
	txtManager->load(tile.type);
	sprite.setTexture(txtManager->get(tile.type));
	sprite.setTextureRect(rect);
	sprite.setRotation(tile.rotation);
}