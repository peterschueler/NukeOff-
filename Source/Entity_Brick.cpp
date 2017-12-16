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
	std::cout << combValue << std::endl;
	vals.insert(std::pair<int, std::pair<int, int> >(21, {160,60}));
	vals.insert(std::pair<int, std::pair<int, int> >(22, {160,80}));
	vals.insert(std::pair<int, std::pair<int, int> >(23, {160,100}));
	vals.insert(std::pair<int, std::pair<int, int> >(24, {160,120}));
	vals.insert(std::pair<int, std::pair<int, int> >(25, {160,140}));
	vals.insert(std::pair<int, std::pair<int, int> >(26, {160,160}));
	vals.insert(std::pair<int, std::pair<int, int> >(27, {160,180}));
	vals.insert(std::pair<int, std::pair<int, int> >(28, {160,200}));
	
	vals.insert(std::pair<int, std::pair<int, int> >(31, {140,60}));
	vals.insert(std::pair<int, std::pair<int, int> >(32, {140,80}));
	vals.insert(std::pair<int, std::pair<int, int> >(33, {140,100}));
	vals.insert(std::pair<int, std::pair<int, int> >(34, {140,120}));
	vals.insert(std::pair<int, std::pair<int, int> >(35, {140,140}));
	vals.insert(std::pair<int, std::pair<int, int> >(36, {140,160}));
	vals.insert(std::pair<int, std::pair<int, int> >(37, {140,180}));
	vals.insert(std::pair<int, std::pair<int, int> >(38, {140,200}));

	vals.insert(std::pair<int, std::pair<int, int> >(41, {120,60}));
	vals.insert(std::pair<int, std::pair<int, int> >(42, {120,80}));
	vals.insert(std::pair<int, std::pair<int, int> >(43, {120,100}));
	vals.insert(std::pair<int, std::pair<int, int> >(44, {120,120}));
	vals.insert(std::pair<int, std::pair<int, int> >(45, {120,140}));
	vals.insert(std::pair<int, std::pair<int, int> >(46, {120,160}));
	vals.insert(std::pair<int, std::pair<int, int> >(47, {120,180}));
	vals.insert(std::pair<int, std::pair<int, int> >(48, {120,200}));
	
	vals.insert(std::pair<int, std::pair<int, int> >(51, {100,60}));
	vals.insert(std::pair<int, std::pair<int, int> >(52, {100,80}));
	vals.insert(std::pair<int, std::pair<int, int> >(53, {100,100}));
	vals.insert(std::pair<int, std::pair<int, int> >(54, {100,120}));
	vals.insert(std::pair<int, std::pair<int, int> >(55, {100,140}));
	vals.insert(std::pair<int, std::pair<int, int> >(56, {100,160}));
	vals.insert(std::pair<int, std::pair<int, int> >(57, {100,180}));
	vals.insert(std::pair<int, std::pair<int, int> >(58, {100,200}));
	
	vals.insert(std::pair<int, std::pair<int, int> >(61, {80,60}));
	vals.insert(std::pair<int, std::pair<int, int> >(62, {80,80}));
	vals.insert(std::pair<int, std::pair<int, int> >(63, {80,100}));
	vals.insert(std::pair<int, std::pair<int, int> >(64, {80,120}));
	vals.insert(std::pair<int, std::pair<int, int> >(65, {80,140}));
	vals.insert(std::pair<int, std::pair<int, int> >(66, {80,160}));
	vals.insert(std::pair<int, std::pair<int, int> >(67, {80,180}));
	vals.insert(std::pair<int, std::pair<int, int> >(68, {80,500}));
	
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
	tile.color = Tile::Color::Yellow;
	tile.type = Tile::Type::Default;
	setDestructable(true);
	attachTexture();
}

Entity_Brick::Entity_Brick(Tile tile): sprite(), isDestroyed(false), tile(tile) {
	if (tile.type == Tile::Type::Hard) {
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
	if (tile.type == Tile::Type::Hard) {
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
	if (tile.type == Tile::Type::Default) {
		if (tile.color == Tile::Color::Red) {
			filePath = filePath + "Red.png";
		} else if (tile.color == Tile::Color::Green) {
			filePath = filePath + "Green.png";
		} else if (tile.color == Tile::Color::Blue) {
			filePath = filePath + "Blue.png";
		} else if (tile.color == Tile::Color::Yellow) {
			filePath = filePath + "Yellow.png";
		} else if (tile.color == Tile::Color::Purple) {
			filePath = filePath + "Purple.png";
		} else if (tile.color == Tile::Color::White) {
			filePath = filePath + "White.png";
		}
	} else if (tile.type == Tile::Type::Hard) {
		filePath = filePath + "Hard.png";
	} else if (tile.type == Tile::Type::LifeUp) {
		filePath = filePath + "LifeUp.png";
	} else if (tile.type == Tile::Type::SpeedUp) {
		filePath = filePath + "SpeedUp.png";
	} else if (tile.type == Tile::Type::SpeedDown) {
		filePath = filePath + "SpeedDown.png";
	} else if (tile.type == Tile::Type::Bomb) {
		filePath = filePath + "Bomb.png";
	} else if (tile.type == Tile::Type::Nuke) {
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