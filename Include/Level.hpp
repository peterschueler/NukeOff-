#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>

struct Tile {
	int x,y;
	enum class Type {
		Default,
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
	};
};

class Level {
public:
	// Loads Empty Level
	Level();
	// Loads Level From File
	// Data Format: 
	// x-value y-value type (Default, Life up, speed Up, speed Down, Bomb, Nuke) color (Red, Green, Blue, Yellow)
	Level(std::string);
	// Loads Level With Parameters: Tiles
	Level(std::vector<Tile>);
	
	void setNumber(unsigned int);
	unsigned int getNumber() const;
	
private:
	std::vector<Tile> loadFromFile(std::string);

	unsigned int number;
	std::vector<Tile> tiles;
};

#endif