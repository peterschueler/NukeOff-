#include "../Include/Game.hpp"

Game::Game(sf::RenderWindow& win) : window(win), bounds(0.f, 0.f, window.getDefaultView().getSize().x, window.getDefaultView().getSize().y), gameOver(false), currentLevel(-1) {
	if (currentLevel == -1) {
		currentLevel = 1;
	}
}

bool Game::processInput(sf::Event& event) {
	if (event.key.code == sf::Keyboard::Escape) {
		return false;
	}
	return true;
}

bool Game::update(sf::Time delta) {
	if (gameOver) {
		return false;
	}
	return true;
}

void Game::render() {
	window.clear(sf::Color::Green);
	window.display();
}