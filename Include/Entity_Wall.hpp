#ifndef Entity_Wall_hpp
#define Entity_Wall_hpp

#include "Entity.hpp"
#include "Level.hpp"

class TextureManager;

class Entity_Wall : public Entity {
public:
	Entity_Wall(Tile, unsigned int, const std::shared_ptr<TextureManager>&);
	// x, y, rotation, level
	Entity_Wall(int, int, int, Tile::Type, unsigned int, TextureManager&);
	
	void update(sf::Time);
	
	sf::FloatRect borders() const;
	sf::Vector2f getCenter() const;
	
protected:
	void draw(sf::RenderTarget&, sf::RenderStates) const;
	void attachTexture();
	
private:
	sf::Sprite sprite;
	
	Tile tile;
	
	unsigned int level;
	
	std::shared_ptr<TextureManager> txtManager;
};

#endif