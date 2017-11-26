#include "../Include/Level.hpp"

#include <fstream>
#include <sstream>

Level::Level() {
}

Level::Level(std::string fileName) {
	tiles = loadFromFile(fileName);
}

Level::Level(std::vector<Tile> tiles) {
	tiles = std::move(tiles);
}

std::vector<Tile> Level::loadFromFile(std::string fileName) {
	std::ifstream infile(fileName);
	std::string line;
	std::vector<std::string> lines; 
	while (std::getline(infile, line, '\n')) {
		lines.push_back(line);
	}
	
	std::vector<Tile> lvlTiles;
	for (auto liner : lines) {
		std::vector<std::string> tokens;
		std::stringstream lineStream(liner);
		while (std::getline(lineStream, line, ':')) {
			tokens.push_back(line);
		}
		Tile tile = tokensToTile(tokens);
		lvlTiles.push_back(tile);
	}
	return lvlTiles;
}

Tile Level::tokensToTile(std::vector<std::string> tokens) {
	Tile tile;
	tile.x = std::stoi(tokens[0]);
	tile.y = std::stoi(tokens[1]);
	
	auto type = tokens[2];
	if (type == "D") {
		tile.type = Tile::Type::Default;
	} else if (type == "H") {
		tile.type = Tile::Type::Hard;
	} else if (type == "L") {
		tile.type = Tile::Type::LifeUp;
	} else if (type == "U") {
		tile.type = Tile::Type::SpeedUp;
	} else if (type == "D") {
		tile.type = Tile::Type::SpeedDown;
	} else if (type == "B") {
		tile.type = Tile::Type::Bomb;
	} else if (type == "N") {
		tile.type = Tile::Type::Nuke;
	} else {
		tile.type = Tile::Type::Default;
	}
	
	auto color = tokens[3];
	if (color == "R") {
		tile.color = Tile::Color::Red;
	} else if (color == "G") {
		tile.color = Tile::Color::Green;
	} else if (color == "B") {
		tile.color = Tile::Color::Blue;	
	} else if (color == "Y") {
		tile.color = Tile::Color::Yellow;
	} else if (color == "P") {
		tile.color = Tile::Color::Purple;
	} else if (color == "W") {
		tile.color = Tile::Color::White;
	} else {
		tile.color = Tile::Color::Yellow;
	}
	return tile;
}

void Level::setNumber(unsigned int num) {
	number = num;
}

unsigned int Level::getNumber() const {
	return number;
}