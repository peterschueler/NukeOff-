#include "../Include/Game.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

#include "../Include/Entity_Brick.hpp"
#include "../Include/Entity_Wall.hpp"
#include "../Include/Entity_Paddle.hpp"
#include "../Include/Entity_Ball.hpp"
#include "../Include/TextureManager.hpp"

Game::Game(sf::RenderWindow& win) : window(win), bounds(0.f, 0.f, window.getDefaultView().getSize().x, window.getDefaultView().getSize().y), gameOver(false), upperBorder(40), lowerBorder(200) {
	txtManager = new TextureManager();
	
	paddle = new Entity_Paddle();
	paddle->setPosition(300, 100);
	
	auto ballTile = Tile(0,0,0,Tile::Type::Ball_Default);
	ball = new Entity_Ball(ballTile, *txtManager);
	ball->setPosition(280, 80);
	
	initializeLevels();	
	setupLevel(0, currentLevel);
}

bool Game::processInput(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape) {
			return false;
		} else if (event.key.code == sf::Keyboard::F) {
			selectLevel(0);
		} else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
			paddle->moveUp(60);
		} else if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
			paddle->moveUp(-60);
		} else if (event.key.code == sf::Keyboard::L) {
			paddle->setState(Entity_Paddle::Paddle_State::Long);
		} else if (event.key.code == sf::Keyboard::Space) {
			ball->setDirection(20, 30);
		}
	} else if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Up) {
			paddle->stop();
		} 
	}
	return true;
}

bool Game::update(sf::Time delta) {
	if (gameOver) {
		return false;
	}
	paddle->update(delta);
	ball->update(delta);
	checkCollisions();
	
	auto brick_iter = bricks.begin();
	while (brick_iter != bricks.end()) {
		auto br = *brick_iter;
		if (br->getDestroyed() == true) {
			brick_iter = bricks.erase(brick_iter);
		} else {
			++brick_iter;
		}
	}
	
	return true;
}

void Game::render() {
	window.clear(sf::Color::Black);
	window.draw(*paddle);
	window.draw(*ball);
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
	for (auto lvl : levels) {
		if (lvl->getNumber() == number) {
			level = lvl;
			std::cout << "Level " << number << " was found." << std::endl;
		} else {
			std::cout << "Level " << number << " not found." << std::endl;
		}
	}
	for (auto tile : level->getTiles()) {
		Entity_Brick* br = new Entity_Brick(tile, *txtManager);
		bricks.push_back(br);
	}
	
	for (auto wall : level->getWallTiles()) {
		Entity_Wall* wl = new Entity_Wall(wall, number, *txtManager);
		walls.push_back(wl);
	}
}

void Game::checkCollisions() {
	if (paddle->getPosition().y <= upperBorder) {
		paddle->setPosition(paddle->getPosition().x, upperBorder);
	}
	if (paddle->getAdjustedPosition().y >= lowerBorder) {
		paddle->setAdjustedPosition(paddle->getAdjustedPosition().x, lowerBorder);
	}
	if (paddle->borders().intersects(ball->borders())) {
		sf::Vector2f padDir = paddle->getDirection();
		if (padDir.y == 0) {
			ball->setDirection(-ball->getDirection().y, ball->getDirection().x);
			return;
		} else {
			ball->setDirection(-ball->getDirection().x, padDir.y);
			return;
		}
	}
	
	// TODO: add checks for relative direction of ball. (normalize ball vector, compare with brick/wall rect.)
	
	for (auto iter = bricks.begin(); iter != bricks.end(); ++iter) {
		Entity_Brick* br = *iter;
		
		if (br->borders().intersects(ball->borders())) {
			ball->setDirection(-ball->getDirection().x, ball->getDirection().y);
			br->destroy();
			return;
		}
	}

	for (auto iter = walls.begin(); iter != walls.end(); ++iter) {
		Entity_Wall* wl = *iter;
		if (wl->borders().intersects(ball->borders())) {
			if (ball->getPosition().x > 25) {
				ball->setDirection(ball->getDirection().x, -ball->getDirection().y);
				return;
			} else {
				ball->setDirection(-ball->getDirection().x, -ball->getDirection().y);
				return;
			}
		}
	}
}