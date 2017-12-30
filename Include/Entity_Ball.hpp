#ifndef Entity_Ball_hpp
#define Entity_Ball_hpp

#include "Entity.hpp"

class Entity_Ball : public Entity {
public:
	Entity_Ball();
	
	void update(sf::Time);
	sf::FloatRect borders() const;
	
	void setDirection(float, float);
	sf::Vector2f getDirection() const;
		
protected:
	void draw(sf::RenderTarget&, sf::RenderStates) const;
	void attachTexture();
	
private:
	sf::CircleShape sprite;
	sf::Texture texture;
	sf::Vector2f direction;
};

#endif