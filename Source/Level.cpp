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
	
	auto type = tokens[2] + tokens[3];
	if (type == "DR") {
		tile.type = Tile::Type::Brick_Basic_Red;
	} else if (type == "DG") {
		tile.type = Tile::Type::Brick_Basic_Green;
	} else if (type == "DB") {
		tile.type = Tile::Type::Brick_Basic_Blue;
	} else if (type == "DY") {
		tile.type = Tile::Type::Brick_Basic_Yellow;
	} else if (type == "DP") {
		tile.type = Tile::Type::Brick_Basic_Purple;
	} else if (type == "DW") {
		tile.type = Tile::Type::Brick_Basic_White;
	} else if (type == "H") {
		tile.type = Tile::Type::Brick_Hard;
	} else if (type == "L") {
		tile.type = Tile::Type::Brick_LifeUp;
	} else if (type == "U") {
		tile.type = Tile::Type::Brick_SpeedUp;
	} else if (type == "D") {
		tile.type = Tile::Type::Brick_SpeedDown;
	} else if (type == "B") {
		tile.type = Tile::Type::Brick_Bomb;
	} else if (type == "N") {
		tile.type = Tile::Type::Brick_Nuke;
	} else {
		tile.type = Tile::Type::Default;
	}

	return tile;
}

void Level::buildWall() {
		// upper line: corner (0 rot) medium large small large small medium large corner (90 rot)
		// left line small medium large {-90 rot}
		// lower line: corner (270 rot) medium large small large small medium large {180 rot} corner (180 rot)
		
		std::vector<Tile> upperWalls = {Tile(0, 20, 0, Tile::Type::Wall_Corner_Yellow), Tile(20,20,0, Tile::Type::Wall_Medium_Yellow), Tile(50,20,0, Tile::Type::Wall_Long_Yellow), Tile(110,20,0,Tile::Type::Wall_Short_Yellow), Tile(130,20,0,Tile::Type::Wall_Long_Yellow), Tile(190,20,0,Tile::Type::Wall_Short_Yellow), Tile(210,20,0,Tile::Type::Wall_Long_Yellow), Tile(270,20,0,Tile::Type::Wall_Medium_Yellow), Tile(320, 20, 90, Tile::Type::Wall_Corner_Yellow)};
		
		std::vector<Tile> leftWalls = {Tile(0, 60, -90, Tile::Type::Wall_Short_Yellow), Tile(0, 90, -90, Tile::Type::Wall_Medium_Yellow), Tile(0, 150, -90, Tile::Type::Wall_Long_Yellow), Tile(0,180, -90, Tile::Type::Wall_Medium_Yellow), Tile(0,200, -90, Tile::Type::Wall_Short_Yellow), Tile(0, 220, -90, Tile::Type::Wall_Short_Yellow)};
		
		std::vector<Tile> lowerWalls = {Tile(0, 240, 270, Tile::Type::Wall_Corner_Yellow), Tile(50,240,180, Tile::Type::Wall_Medium_Yellow), Tile(110,240,180, Tile::Type::Wall_Long_Yellow), Tile(130,240,180,Tile::Type::Wall_Short_Yellow), Tile(190,240,180,Tile::Type::Wall_Long_Yellow), Tile(210,240,180,Tile::Type::Wall_Short_Yellow),Tile(270,240,180,Tile::Type::Wall_Long_Yellow), Tile(300,240,180,Tile::Type::Wall_Medium_Yellow), Tile(320, 240, 180, Tile::Type::Wall_Corner_Yellow)};
		
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

std::vector<Tile> Level::getWallTiles() const {
	return walls;
}