#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>
#include <iostream>

struct Tile {
	int x,y;
	enum class Type {
		Default,
		Hard,
		LifeUp,
		SpeedUp,
		SpeedDown,
		Bomb,
		Nuke,
	};
	enum class Color {
		Red,
		Green,
		Blue,
		Yellow,
		Purple,
		White,
	};
	Type type;
	Color color;
};

struct Wall_Tile {
	int x, y;
	int rotation;
	enum class Type {
		Long,
		Medium,
		Short,
		Corner,
	};
	Type type;
	
	public:
		Wall_Tile(): x(0), y(0), rotation(0), type(Wall_Tile::Type::Medium) {
		}
	
		Wall_Tile(int _x, int _y, int _rotation, std::string _type) {
			x = _x;
			y = _y;
			rotation = _rotation;
			if (_type == "Long") {
				type = Wall_Tile::Type::Long;
			} else if (_type == "Medium") {
				type = Wall_Tile::Type::Medium;
			} else if (_type == "Short") {
				type = Wall_Tile::Type::Short;
			} else if (_type == "Corner") {
				type = Wall_Tile::Type::Corner;
			} else {
				type = Wall_Tile::Type::Medium;
				std::cout << "WARNING: No type assigned on construction. Using default Medium." << std::endl;
			}
		}
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
	std::vector<Wall_Tile> getWallTiles() const;
	
private:
	std::vector<Tile> loadFromFile(std::string);
	Tile tokensToTile(std::vector<std::string>);
		
	void buildWall();

	unsigned int number;
	std::vector<Tile> tiles;
	std::vector<Wall_Tile> walls;
};

#endif