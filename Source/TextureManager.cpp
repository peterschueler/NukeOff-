#include "../Include/TextureManager.hpp"

void TextureManager::load(Tile::Type _type) {
	auto texture = std::make_shared<sf::Texture>();
	std::string path = typeToFileName(_type);
	if (!texture->loadFromFile(path)) {
		std::cerr << "ERROR: Couldn't load texture!"  << std::endl;
	}
	textureMap.insert(std::make_pair(_type, std::move(texture)));
}

sf::Texture& TextureManager::get(Tile::Type _type) const {
	auto texture = textureMap.find(_type);
	return *texture->second;
}

std::string TextureManager::typeToFileName(Tile::Type _type) const {
	std::string brickPath = "Assets/Textures/Bricks/Default/Brick_";
	std::string wallPath = "Assets/Textures/Walls/Default/Wall_";
	std::string ballParth = "Assets/Textures/Balls/Default/Ball_";
	std::string paddlePath = "Assets/Textures/Objects/Default/Paddle_";
	std::string defaultPath = "Assets/Textures/Defaults/white.png";
	std::string backgroundPath = "Assets/Textures/Backgrounds/Default/Background_";
	
	switch(_type) {
	case Tile::Type::Default:
		return defaultPath;
	case Tile::Type::Brick_Basic_Red:
		return brickPath + "Red.png";
	case Tile::Type::Brick_Basic_Green:
		return brickPath + "Green.png";
	case Tile::Type::Brick_Basic_Blue:
		return brickPath + "Blue.png";
	case Tile::Type::Brick_Basic_Yellow:
		return brickPath + "Yellow.png";
	case Tile::Type::Brick_Basic_Purple:
		return brickPath + "Purple.png";
	case Tile::Type::Brick_Basic_White:
		return brickPath + "White.png";
	case Tile::Type::Brick_Hard:
		return brickPath + "Hard.png";
	case Tile::Type::Brick_LifeUp:
		return brickPath + "LifeUp.png";
	case Tile::Type::Brick_SpeedUp:
		return brickPath + "SpeedUp.png";
	case Tile::Type::Brick_SpeedDown:
		return brickPath + "SpeedDown.png";
	case Tile::Type::Brick_Bomb:
		return brickPath + "Bomb.png";
	case Tile::Type::Brick_Nuke:
		return brickPath + "Nuke.png";
	case Tile::Type::Wall_Long_Yellow:
		return wallPath + "Long.png";
	case Tile::Type::Wall_Short_Yellow:
		return wallPath + "Short.png";
	case Tile::Type::Wall_Medium_Yellow:
		return wallPath + "Medium.png";
	case Tile::Type::Wall_Corner_Yellow:
		return wallPath + "Corner.png";
	case Tile::Type::Ball_Default:
		return ballParth + "Default.png";
	case Tile::Type::Paddle_Short:
		return paddlePath + "Short.png";
	case Tile::Type::Paddle_Long:
		return paddlePath + "Long.png";
	case Tile::Type::Background_01:
		return backgroundPath + "01.png";
	case Tile::Type::Background_02:
		return backgroundPath + "02.png";
	case Tile::Type::Background_03:
		return backgroundPath + "03.png";
	}
}