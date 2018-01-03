#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <string>
#include <map>

#include <SFML/Graphics.hpp>

#include "Level.hpp"

class TextureManager {
public:
	TextureManager() {};
	
	void load(Tile::Type);
	
	sf::Texture& get(Tile::Type) const;
	
private:
	std::string typeToFileName(Tile::Type) const;
	
private:
	std::map<Tile::Type, sf::Texture*> textureMap;
};

#endif