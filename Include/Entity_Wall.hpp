#ifndef Entity_Wall_hpp
#define Entity_Wall_hpp

#include "Entity.hpp"
#include "Level.hpp"

class Entity_Wall : public Entity {
public:
	Entity_Wall();
	Entity_Wall(Wall_Tile, unsigned int);
	// x, y, rotation, level
	Entity_Wall(int, int, int, std::string, unsigned int);
	
	void update(sf::Time);
	
	sf::FloatRect borders() const;
	
protected:
	void draw(sf::RenderTarget&, sf::RenderStates) const;
	void attachTexture();
	
private:
	sf::Sprite sprite;
	sf::Texture texture;
	
	Wall_Tile tile;
	
	unsigned int level;
};

#endif