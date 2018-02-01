#ifndef Entity_Background_hpp
#define Entity_Background_hpp

#include "Entity.hpp"
#include "Tile.hpp"

class TextureManager;

class Entity_Background : public Entity {
public:
	Entity_Background();
	Entity_Background(Tile, const std::shared_ptr<TextureManager>&);
	
	void update(sf::Time);
	sf::FloatRect borders() const;
	
	void setDirection(float, float);
	sf::Vector2f getDirection() const;
	
protected:
	void draw(sf::RenderTarget&, sf::RenderStates) const;
	void attachTexture();
	
private:
	sf::Sprite sprite;
	Tile tile;
	
	sf::Vector2f direction;
	
	std::shared_ptr<TextureManager> txtManager;
};

#endif