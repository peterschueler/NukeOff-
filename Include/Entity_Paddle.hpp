#ifndef ENTITY_PADDLE_HPP
#define ENTITY_PADDLE_HPP

#include "Entity.hpp"

#include "TextureManager.hpp"

class Entity_Paddle : public Entity {
public:
	Entity_Paddle();
	Entity_Paddle(Tile, const std::shared_ptr<TextureManager>&);
	
	void update(sf::Time);	
	
	sf::FloatRect borders() const;
	void setAdjustedPosition(float, float);
	sf::Vector2f getAdjustedPosition() const;
	
	void moveUp(float);
	sf::Vector2f getDirection() const {
		return direction;
	};
	void stop();
	
protected:
	void draw(sf::RenderTarget&, sf::RenderStates) const;
	void attachTexture();
	
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f direction;
	
	Tile tile;
	
	std::shared_ptr<TextureManager> txtManager;
};

#endif