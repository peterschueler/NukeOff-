#ifndef ENTITY_BRICK_HPP
#define ENTITY_BRICK_HPP

#include "Entity.hpp"
#include "Tile.hpp"

#include <map>

class TextureManager;

std::pair<int, int> convertTileSpaceToRealSpace(Tile);

class Entity_Brick : public Entity {
public:
	Entity_Brick();
	Entity_Brick(Tile, const std::shared_ptr<TextureManager>&);
	// used for chrome
	Entity_Brick(std::string, TextureManager&);
	
	void update(sf::Time);
	
	sf::FloatRect borders() const;
	sf::Vector2f getCenter() const;
	
	void setDirection(float, float);
	sf::Vector2f getDirection() const;
	
	void destroy();
	bool getDestroyed() const;
	
	void setDestructable(bool);
	bool getGestructable() const;
	
	Tile::Type getType() const;
	sf::Vector2f getRelativePosition() const;
	unsigned int getValue() const;
	
protected:
	void draw(sf::RenderTarget&, sf::RenderStates) const;
	void attachTexture();
	
private:

	void updateValue(Tile::Type);

	sf::Sprite sprite;
	
	Tile tile;
	sf::Vector2f direction;
	
	bool isDestroyed;
	bool isDestructable;
	bool hasCollided;
	
	float destructTimer;
	
	unsigned int value;
	
	std::shared_ptr<TextureManager> txtManager;
};

#endif