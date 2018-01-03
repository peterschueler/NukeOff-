#ifndef ENTITY_BRICK_HPP
#define ENTITY_BRICK_HPP

#include "Entity.hpp"
#include "Level.hpp"

#include <map>

class TextureManager;

std::pair<int, int> convertTileSpaceToRealSpace(Tile);

class Entity_Brick : public Entity {
public:
	Entity_Brick();
	Entity_Brick(Tile, TextureManager&);
	// used for chrome
	Entity_Brick(std::string, TextureManager&);
	
	void update(sf::Time);
	
	sf::FloatRect borders() const;
	
	void destroy();
	bool getDestroyed() const;
	
	void setDestructable(bool);
	bool getGestructable() const;
	
protected:
	void draw(sf::RenderTarget&, sf::RenderStates) const;
	void attachTexture();
	
private:

	sf::Sprite sprite;
	sf::Texture texture;
	
	Tile tile;
	
	bool isDestroyed;
	bool isDestructable;
	
	TextureManager* txtManager;
};

#endif