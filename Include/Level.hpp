#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>
#include <iostream>

#include "Tile.hpp"

class Level {
public:
	// Loads Empty Level
	Level();
	// Loads Level From File
	// Data Format: 
	// One line, one tile. Values are separated with ':'
	// x-value y-value type (Default, Life up, speed Up, speed Down, Bomb, Nuke) color (Red, Green, Blue, Yellow)
	// Example 2:4:D:R
	Level(std::string);
	// Loads Level With Parameters: Tiles
	Level(std::vector<Tile>);
	
	void setNumber(unsigned int);
	unsigned int getNumber() const;
	
	std::vector<Tile> getTiles() const;
	std::vector<Tile> getWallTiles() const;
	
private:
	std::vector<Tile> loadFromFile(std::string);
	Tile tokensToTile(std::vector<std::string>);
		
	void buildWall();

	unsigned int number;
	std::vector<Tile> tiles;
	std::vector<Tile> walls;
};

#endif