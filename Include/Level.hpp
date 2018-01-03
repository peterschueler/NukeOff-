#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>
#include <iostream>

struct Tile {	
	enum class Type {
		Default,		// white square, 20x20
		Brick_Basic_Red,
		Brick_Basic_Green,
		Brick_Basic_Blue,
		Brick_Basic_Yellow,
		Brick_Basic_Purple,
		Brick_Basic_White,
		Brick_Hard,
		Brick_LifeUp,
		Brick_SpeedUp,
		Brick_SpeedDown,
		Brick_Bomb,
		Brick_Nuke,
		Wall_Long_Yellow,
		Wall_Short_Yellow,
		Wall_Medium_Yellow,
		Wall_Corner_Yellow,
	};
	
	Tile(): x(0), y(0), rotation(0), type(Tile::Type::Default) {
	}
	
	Tile(int _x, int _y, int _rotation, Tile::Type _type) {
		x = _x;
		y = _y;
		rotation = _rotation;
		type = _type;
	}
	
	Tile::Type getType() const {
		return type;
	}
	int x,y;
	int rotation;
	Type type;
};

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