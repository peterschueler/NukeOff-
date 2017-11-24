#include "../Include/Level.hpp"

Level::Level() {
}

Level::Level(std::string fileName) {
	tiles = loadFromFile(fileName);
}

Level::Level(std::vector<Tile> tiles) {
	tiles = std::move(tiles);
}

std::vector<Tile> Level::loadFromFile(std::string fileName) {
	return tiles;
}

void Level::setNumber(unsigned int num) {
	number = num;
}

unsigned int Level::getNumber() const {
	return number;
}