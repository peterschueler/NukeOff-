#ifndef Entity_Ball_hpp
#define Entity_Ball_hpp

#include "Entity.hpp"
#include "Tile.hpp"

class TextureManager;

class Entity_Ball : public Entity {
public:
	Entity_Ball();
	Entity_Ball(Tile, const std::shared_ptr<TextureManager>&);
	
	void update(sf::Time);
	sf::FloatRect borders() const;
	sf::Vector2f getCenter() const;
	
	void setDirection(float, float);
	sf::Vector2f getDirection() const;
	
	void setSpeed(float);
		
protected:
	void draw(sf::RenderTarget&, sf::RenderStates) const;
	void attachTexture();
	
private:
	sf::CircleShape sprite;
	sf::Vector2f direction;
	float speed;
	
	Tile tile;
	std::shared_ptr<TextureManager> txtManager;
};

#endif