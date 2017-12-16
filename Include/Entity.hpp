#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable, public sf::Transformable {
public:
	virtual void update(sf::Time) = 0;
	
	virtual sf::FloatRect borders() const = 0;
	
protected:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;
	virtual void attachTexture() = 0;
};

#endif