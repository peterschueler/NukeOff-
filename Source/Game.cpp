#include "../Include/Game.hpp"

#include <algorithm>

Game::Game(sf::RenderWindow& win) : window(win), bounds(0.f, 0.f, window.getDefaultView().getSize().x, window.getDefaultView().getSize().y), gameOver(false) {
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

void Game::selectLevel(unsigned int number) {
	for (auto level : levels) {
		if (level.getNumber() == number) {
			currentLevel = &level;
		}
	 }
}

void Game::nextLevel() {
	if (currentLevel->getNumber() == levels.back().getNumber()) {
		selectLevel(1);
	} else {
		selectLevel(currentLevel->getNumber() + 1);
	}
}

void Game::previousLevel() {
	if (currentLevel->getNumber() == levels.front().getNumber()) {
		selectLevel(levels.back().getNumber());
	} else {
		selectLevel(currentLevel->getNumber() - 1);
	}
}

void Game::setupLevels() {
	unsigned int num = 0;
	for (auto level : levels) {
		level.setNumber(num++);
	}
}