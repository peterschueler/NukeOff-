#include "../Include/JumpGame.hpp"

JumpGame::JumpGame(sf::RenderWindow& win, sf::View& vw): window(win), view(vw), bounds(0.f, 0.f, window.getDefaultView().getSize().x, window.getDefaultView().getSize().y), gameOver(false) {
	txtManager = std::make_shared<TextureManager>(TextureManager());
	
	window.setView(view);
	buildLevel();
	
	auto ballTile = Tile(0,0,0,Tile::Type::Ball_Default);
	character = std::make_unique<Entity_Ball>(Entity_Ball(ballTile, txtManager));
	character->setPosition(280,200);
}

bool JumpGame::processInput(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape) {
			return false;
		} else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
			character->setDirection(-30.f, 0.f);
		} else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
			character->setDirection(30.f, 0.f);
		} else if (event.key.code == sf::Keyboard::Space) {
		}
	} else if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
			character->stop();
		}
	}
	return true;
}

bool JumpGame::update(sf::Time delta) {
	if (gameOver) {
		return false;
	}
	character->update(delta);
}

void JumpGame::render() {
	window.clear(sf::Color::Black);
	window.draw(*character);
	window.display();
}

void JumpGame::buildLevel() {
}