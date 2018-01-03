#include "../Include/Entity_Brick.hpp"

#include <iostream>

int combine(int a, int b) {
	int times = 1;
	while (times <= b) {
		times *= 10;
	}
	return a*times + b;
}

std::pair<int, int> convertTileSpaceToRealSpace(Tile tile) {
	std::map<int, std::pair<int, int> > vals;
	int combValue = combine(tile.y, tile.x);
	
	unsigned int xVal = 0;
	unsigned int yVal = 40;
	for (int it = 10; it < 70; it++) {
		yVal += 20;
		if (it > 10 && it < 20) {
			xVal = 180;
		} else if (it > 20 && it < 30) {
			xVal = 160;
		} else if (it > 30 && it < 40) {
			xVal = 140;
		} else if (it > 40 && it < 50) {
			xVal = 120;
		} else if (it > 50 && it < 60) {
			xVal = 100;
		} else if (it > 60 && it < 70) {
			xVal = 80;
		} else if (it > 70 && it < 80) {
			xVal = 60;
		}
		vals.insert(std::pair<int, std::pair<int, int> >(it, {xVal,yVal}));
		if (it % 10 == 0) {
			yVal = 40;
		}
	}
	
	for (auto val : vals) {
		if (combValue == val.first) {
			return val.second;
		}
	}
	return std::make_pair(-100, -100);
}

Entity_Brick::Entity_Brick(): sprite(), isDestroyed(false) {
	tile.x = 0;
	tile.y = 0;
	tile.type = Tile::Type::Default;
	setDestructable(true);
	attachTexture();
}

Entity_Brick::Entity_Brick(Tile tile): sprite(), isDestroyed(false), tile(tile) {
	if (tile.type == Tile::Type::Brick_Hard) {
		setDestructable(false);
	} else {
		setDestructable(true);
	}
	attachTexture();
	std::pair<int, int> coords = convertTileSpaceToRealSpace(tile);
	setPosition(coords.first, coords.second);
}

void Entity_Brick::update(sf::Time) {
}
	
sf::FloatRect Entity_Brick::borders() const {
	sf::FloatRect bounds = getTransform().transformRect(sprite.getGlobalBounds());
	return bounds;
}
	
void Entity_Brick::destroy() {
	isDestroyed = true;
}

bool Entity_Brick::getDestroyed() const {
	return isDestroyed;
}

void Entity_Brick::setDestructable(bool destr) {
	if (tile.type == Tile::Type::Brick_Hard) {
		return;
	}
	isDestructable = destr;
}

bool Entity_Brick::getGestructable() const {
	return isDestructable;
}

void Entity_Brick::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	
	target.draw(sprite, states);
}

void Entity_Brick::attachTexture() {
	std::string filePath = "Assets/Textures/Bricks/Default/Brick_";
	if (tile.type == Tile::Type::Brick_Basic_Red) {
		filePath = filePath + "Red.png";
	} else if (tile.type == Tile::Type::Brick_Basic_Red) {
		filePath = filePath + "Green.png";
	} else if (tile.type == Tile::Type::Brick_Basic_Blue) {
		filePath = filePath + "Blue.png";
	} else if (tile.type == Tile::Type::Brick_Basic_Yellow) {
		filePath = filePath + "Yellow.png";
	} else if (tile.type == Tile::Type::Brick_Basic_Purple) {
		filePath = filePath + "Purple.png";
	} else if (tile.type == Tile::Type::Brick_Basic_White) {
		filePath = filePath + "White.png";
	} else if (tile.type == Tile::Type::Brick_Hard) {
		filePath = filePath + "Hard.png";
	} else if (tile.type == Tile::Type::Brick_LifeUp) {
		filePath = filePath + "LifeUp.png";
	} else if (tile.type == Tile::Type::Brick_SpeedUp) {
		filePath = filePath + "SpeedUp.png";
	} else if (tile.type == Tile::Type::Brick_SpeedDown) {
		filePath = filePath + "SpeedDown.png";
	} else if (tile.type == Tile::Type::Brick_Bomb) {
		filePath = filePath + "Bomb.png";
	} else if (tile.type == Tile::Type::Brick_Nuke) {
		filePath = filePath + "Nuke.png";
	}
	sf::IntRect rect = sf::IntRect(0,0,15,20);
	if (texture.loadFromFile(filePath)) {
		sprite.setTexture(texture);
		sprite.setTextureRect(rect);
	} else {
		std::cerr << "Couldn't load " << filePath << ". Did you misplace the texture file?"<< std::endl; 
	}
}