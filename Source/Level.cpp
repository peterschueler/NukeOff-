#include "../Include/Level.hpp"

#include <fstream>
#include <sstream>

Level::Level() {
}

Level::Level(std::string fileName) {
	buildWall();
	tiles = loadFromFile(fileName);
}

Level::Level(std::vector<Tile> tiles) {
	buildWall();
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

void Level::buildWall() {
		// upper line: corner (0 rot) medium large small large small medium large corner (90 rot)
		// left line small medium large {-90 rot}
		// lower line: corner (270 rot) medium large small large small medium large {180 rot} corner (180 rot)
		
		std::vector<Wall_Tile> upperWalls = {Wall_Tile(0, 20, 0, "Corner"), Wall_Tile(20,20,0, "Medium"), Wall_Tile(50,20,0, "Long"), Wall_Tile(110,20,0,"Short"), Wall_Tile(130,20,0,"Long"), Wall_Tile(190,20,0,"Short"), Wall_Tile(210,20,0,"Long"), Wall_Tile(270,20,0,"Medium"), Wall_Tile(320, 20, 90, "Corner")};
		
		std::vector<Wall_Tile> leftWalls = {Wall_Tile(0, 60, -90, "Short"), Wall_Tile(0, 90, -90, "Medium"), Wall_Tile(0, 150, -90, "Long"), Wall_Tile(0,180, -90, "Medium"), Wall_Tile(0,200, -90, "Short"), Wall_Tile(0, 220, -90, "Short")};
		
		std::vector<Wall_Tile> lowerWalls = {Wall_Tile(0, 240, 270, "Corner"), Wall_Tile(50,240,180, "Medium"), Wall_Tile(110,240,180, "Long"), Wall_Tile(130,240,180,"Short"), Wall_Tile(190,240,180,"Long"), Wall_Tile(210,240,180,"Short"),Wall_Tile(270,240,180,"Long"), Wall_Tile(300,240,180,"Medium"), Wall_Tile(320, 240, 180, "Corner")};
		
		walls.insert(walls.end(), upperWalls.begin(), upperWalls.end());
		walls.insert(walls.end(), leftWalls.begin(), leftWalls.end());
		walls.insert(walls.end(), lowerWalls.begin(), lowerWalls.end());
}

void Level::setNumber(unsigned int num) {
	number = num;
}

unsigned int Level::getNumber() const {
	return number;
}

std::vector<Tile> Level::getTiles() const {
	return tiles;
}

std::vector<Wall_Tile> Level::getWallTiles() const {
	return walls;
}