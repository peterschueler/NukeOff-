#ifndef ENTITY_PADDLE_HPP
#define ENTITY_PADDLE_HPP

#include "Entity.hpp"

class Entity_Paddle : public Entity {
public:
	enum class Paddle_State {
		Long,
		Short,
		Thick,
	};
	
public:
	Entity_Paddle();
	
	void update(sf::Time);	
	
	sf::FloatRect borders() const;
	void setAdjustedPosition(float, float);
	sf::Vector2f getAdjustedPosition() const;
	void setState(Entity_Paddle::Paddle_State);
	
	void moveUp(float);
	void stop();
	
protected:
	void draw(sf::RenderTarget&, sf::RenderStates) const;
	void attachTexture();
	
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f direction;
	
	Paddle_State state;
};

#endif