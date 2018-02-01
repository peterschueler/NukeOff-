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
	
	void destroy();
	bool getDestroyed() const;
	
	void setDestructable(bool);
	bool getGestructable() const;
	
protected:
	void draw(sf::RenderTarget&, sf::RenderStates) const;
	void attachTexture();
	
private:

	sf::Sprite sprite;
	
	Tile tile;
	
	bool isDestroyed;
	bool isDestructable;
	
	std::shared_ptr<TextureManager> txtManager;
};

#endif