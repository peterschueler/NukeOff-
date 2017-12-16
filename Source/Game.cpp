#include "../Include/Game.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

#include "../Include/Entity_Brick.hpp"
#include "../Include/Entity_Wall.hpp"

Game::Game(sf::RenderWindow& win) : window(win), bounds(0.f, 0.f, window.getDefaultView().getSize().x, window.getDefaultView().getSize().y), gameOver(false) {
	initializeLevels();	
	setupLevel(0, currentLevel);
}

bool Game::processInput(sf::Event& event) {
	if (event.key.code == sf::Keyboard::Escape) {
		return false;
	} else if (event.key.code == sf::Keyboard::F) {
		selectLevel(0);
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
	window.clear(sf::Color::Black);
	for (auto brick : bricks) {
		window.draw(*brick);
	}
	for (auto wall : walls) {
		window.draw(*wall);
	}
	window.display();
}

void Game::selectLevel(unsigned int number) {
	setupLevel(number, currentLevel);
}

void Game::nextLevel() {
	if (currentLevel->getNumber() == levels.back()->getNumber()) {
		selectLevel(1);
	} else {
		selectLevel(currentLevel->getNumber() + 1);
	}
}

void Game::previousLevel() {
	if (currentLevel->getNumber() == levels.front()->getNumber()) {
		selectLevel(levels.back()->getNumber());
	} else {
		selectLevel(currentLevel->getNumber() - 1);
	}
}

void Game::initializeLevels() {
	std::ifstream infile("Assets/Levels/LevelList.txt");
	std::string line;
	std::vector<std::string> lvls;
	while (std::getline(infile, line, '\n')) {
		lvls.push_back(line);
	}
	for (auto lvl : lvls) {
		auto name = "Assets/Levels/" + lvl;
		std::cout << "Loading " << name << std::endl;
		Level *newLevel = new Level(name);
		newLevel->setNumber(0);
		levels.push_back(newLevel);
	}
	
	for (unsigned int it = 0; it < levels.size(); it++) {
		levels[it]->setNumber(it);
	}
}

void Game::setupLevel(unsigned int number, Level* level) {
	std::cout << levels.size() << std::endl;
	for (auto lvl : levels) {
		if (lvl->getNumber() == number) {
			level = lvl;
			std::cout << "Level " << number << " was found." << std::endl;
		} else {
			std::cout << "Level " << number << " not found." << std::endl;
		}
	}
	for (auto tile : level->getTiles()) {
		Entity_Brick* br = new Entity_Brick(tile);
		bricks.push_back(br);
	}
	
	for (auto wall : level->getWallTiles()) {
		Entity_Wall* wl = new Entity_Wall(wall, number);
		walls.push_back(wl);
	}
}