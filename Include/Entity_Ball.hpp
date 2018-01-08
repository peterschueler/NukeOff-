#ifndef Entity_Ball_hpp
#define Entity_Ball_hpp

#include "Entity.hpp"
#include "Level.hpp"

class TextureManager;

class Entity_Ball : public Entity {
public:
	Entity_Ball();
	Entity_Ball(Tile, TextureManager&);
	
	void update(sf::Time);
	sf::FloatRect borders() const;
	
	void setDirection(float, float);
	sf::Vector2f getDirection() const;
		
protected:
	void draw(sf::RenderTarget&, sf::RenderStates) const;
	void attachTexture();
	
private:
	sf::CircleShape sprite;
	sf::Vector2f direction;
	
	Tile tile;
	TextureManager* txtManager;
};

#endif