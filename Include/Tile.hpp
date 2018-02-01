#ifndef Tile_hpp
#define Tile_hpp

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
		Ball_Default,
		Paddle_Short,
		Paddle_Long,
		Background_01,
		Background_02,
		Background_03,
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

#endif