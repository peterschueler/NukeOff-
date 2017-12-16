#include "../Include/Entity_Wall.hpp"

#include <iostream>

Entity_Wall::Entity_Wall() : sprite(), level(0) {
	attachTexture();
}

Entity_Wall::Entity_Wall(Wall_Tile wl, unsigned int lvl) : sprite(), tile(wl), level(lvl) {
	attachTexture();
	setPosition(wl.x, wl.y);
}

Entity_Wall::Entity_Wall(int x, int y, int rot, std::string ty, unsigned int lvl) : sprite(), tile(x,y,rot, ty), level(lvl) {
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
	if (tile.type == Wall_Tile::Type::Long) {
		filePath = filePath + "Long.png";
		x = 60;
	} else if (tile.type == Wall_Tile::Type::Medium) {
		filePath = filePath + "Medium.png";
		x = 30;
	} else if (tile.type == Wall_Tile::Type::Short) {
		filePath = filePath + "Short.png";	
		x = 20;
	} else if (tile.type == Wall_Tile::Type::Corner) {
		filePath = filePath + "Corner.png";
		x = 20;
		y = 20;
	}
	sprite.setOrigin(sprite.getGlobalBounds().height / 2, sprite.getGlobalBounds().width / 2);
	sf::IntRect rect = sf::IntRect(0,0,x,y);
	if (texture.loadFromFile(filePath)) {
		sprite.setTexture(texture);
		sprite.setTextureRect(rect);
		sprite.setRotation(tile.rotation);
	} else {
		std::cerr << "Couldn't load " << filePath << ". Did you try to access a non-existing level?" << std::endl;
	}
}