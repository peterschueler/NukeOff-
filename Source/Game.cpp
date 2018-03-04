#include "../Include/Game.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

Game::Game(sf::RenderWindow& win, sf::View& vw) : window(win), view(vw), bounds(0.f, 0.f, window.getDefaultView().getSize().x, window.getDefaultView().getSize().y), gameOver(false), points(0), upperBorder(40), lowerBorder(200), ballSpeedScale(1) {
	txtManager = std::make_shared<TextureManager>(TextureManager());
	
	window.setView(view);
	
	resetLevel(1);
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
		}  else if (event.key.code == sf::Keyboard::Space) {
			ball->setDirection(30, 30);
			currentBackground->setDirection(100,100);
		} else if (event.key.code == sf::Keyboard::T) {
			testFunc();
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
	} else {
		paddle->update(delta);
		ball->update(delta);
		currentBackground->update(delta);
		checkCollisions();
	
		auto brick_iter = bricks.begin();
		while (brick_iter != bricks.end()) {
			auto br = *brick_iter;
			br->update(delta);
			if (br->getDestroyed() == true) {
				brick_iter = bricks.erase(brick_iter);
			} else {
				++brick_iter;
			}
		}
	
		if (ball->getPosition().x > 330) {
			gameOver = true;
		}
	
		if (bricks.size() == 0) {
			nextLevel();
		}
	
		return true;
	}
}

void Game::render() {
	window.clear(sf::Color::Black);
	window.draw(*currentBackground);
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
	if (currentLevel->getNumber() == levels.back()->getNumber() || currentLevel->getNumber() == 0) {
		selectLevel(0);
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
		auto newLevel = std::make_shared<Level>(name);
		newLevel->setNumber(0);
		levels.push_back(newLevel);
	}
	
	for (unsigned int it = 0; it < levels.size(); it++) {
		levels[it]->setNumber(it);
	}
	currentLevel = levels.front();
}

void Game::setupLevel(unsigned int number, std::shared_ptr<Level> level) {
	resetLevel(number);
	
	for (auto lvl : levels) {
		if (lvl->getNumber() == number) {
			level = lvl;
		} else {
			std::cerr << "Level " << number << " not found." << std::endl;
		}
	}
	for (auto tile : level->getTiles()) {
		auto br = std::make_shared<Entity_Brick>(Entity_Brick(tile, txtManager));
		bricks.push_back(br);
	}
	
	for (auto wall : level->getWallTiles()) {
		auto wl = std::make_shared<Entity_Wall>(Entity_Wall(wall, number, txtManager));
		walls.push_back(wl);
	}
	currentLevel = level;
}

void Game::resetLevel(unsigned int number) {
	bricks.clear();
	walls.clear();
	
	// TODO: Make This Scalable.
	if (number == 1) {
		auto bckTile = Tile(0,0,0,Tile::Type::Background_01);
		currentBackground = std::make_unique<Entity_Background>(Entity_Background(bckTile,txtManager));
		currentBackground->setPosition(-400,-400);
	} else if (number == 2) {
		auto bckTile = Tile(0,0,0,Tile::Type::Background_02);
		currentBackground = std::make_unique<Entity_Background>(Entity_Background(bckTile,txtManager));
		currentBackground->setPosition(-400,-400);
	} else if (number == 3) {
		auto bckTile = Tile(0,0,0,Tile::Type::Background_03);
		currentBackground = std::make_unique<Entity_Background>(Entity_Background(bckTile,txtManager));
		currentBackground->setPosition(-400,-400);
	} else if (number == 4) {
		auto bckTile = Tile(0,0,0,Tile::Type::Background_04);
		currentBackground = std::make_unique<Entity_Background>(Entity_Background(bckTile,txtManager));
		currentBackground->setPosition(-400,-400);
	} else if (number == 5) {
		auto bckTile = Tile(0,0,0,Tile::Type::Background_05);
		currentBackground = std::make_unique<Entity_Background>(Entity_Background(bckTile,txtManager));
		currentBackground->setPosition(-400,-400);
	} else {
		std::cerr << "ERROR: Couldn't load background for level " << number << std::endl;
	}
	currentBackground->setScale(1920, 2560);

	auto paddleTile = Tile(0,0,0,Tile::Type::Paddle_Short);
	paddle = std::make_unique<Entity_Paddle>(Entity_Paddle(paddleTile, txtManager));
	paddle->setPosition(300, 100);

	auto ballTile = Tile(0,0,0,Tile::Type::Ball_Default);
	ball = std::make_unique<Entity_Ball>(Entity_Ball(ballTile, txtManager));
	ball->setPosition(280, 80);
}

void Game::checkCollisions() {
	// MARK: Paddle Collisions
	if (paddle->getPosition().y <= upperBorder) {
		paddle->setPosition(paddle->getPosition().x, upperBorder);
	}
	if (paddle->getAdjustedPosition().y >= lowerBorder) {
		paddle->setAdjustedPosition(paddle->getAdjustedPosition().x, lowerBorder);
	}
	if (paddle->borders().intersects(ball->borders())) {
		sf::Vector2f padDir = paddle->getDirection();
		if (padDir.y == 0) {
			ball->setDirection(-ball->getDirection().x, ball->getDirection().y);
			currentBackground->setDirection(-currentBackground->getDirection().x, currentBackground->getDirection().y);
			return;
		} else {
			ball->setDirection(-ball->getDirection().x, padDir.y);
			currentBackground->setDirection(-currentBackground->getDirection().x, padDir.y);
			return;
		}
	}
	
	// MARK: Brick Collisions
	for (auto iter = bricks.begin(); iter != bricks.end(); ++iter) {
		auto br = *iter;
		
		auto adjustedWidth = br->borders().width - 1;
		auto adjustedHeight = br->borders().height - 1;
		
		auto left = br->borders().left + 1;
		auto right = br->borders().left + adjustedWidth;
		
		auto top = br->borders().top + 1;
		auto bottom = br->borders().top + adjustedHeight;
		
		if (br->borders().intersects(ball->borders())) {
			// MARK: Pointage
			points += br->getValue();
			
			// MARK: Brick Collisions - Speed
			if (br->getType() == Tile::Type::Brick_SpeedUp) {
				ballSpeedScale += 0.1;
			} else if (br->getType() == Tile::Type::Brick_SpeedDown) {
				ballSpeedScale -= 0.1;
			}
			ball->setSpeed(ballSpeedScale);
		
			// MARK: Ball Orientation
			if (ball->getPosition().y < top && ball->getPosition().x > left && ball->getPosition().x < right) {
				ball->setDirection(ball->getDirection().x, -ball->getDirection().y);
				currentBackground->setDirection(currentBackground->getDirection().x, -currentBackground->getDirection().y);
			} else if (ball->getPosition().y > bottom && ball->getPosition().x > left && ball->getPosition().x < left) {
				ball->setDirection(ball->getDirection().x, -ball->getDirection().y);
				currentBackground->setDirection(currentBackground->getDirection().x, -currentBackground->getDirection().y);
			} else if (ball->getPosition().x < left && ball->getPosition().y > top && ball->getPosition().y < bottom) {
				ball->setDirection(-ball->getDirection().x, ball->getDirection().y);
				currentBackground->setDirection(-currentBackground->getDirection().x, currentBackground->getDirection().y);
			} else if (ball->getPosition().x > right && ball->getPosition().y > top && ball->getPosition().y < bottom) {
				ball->setDirection(-ball->getDirection().x, ball->getDirection().y);
				currentBackground->setDirection(-currentBackground->getDirection().x, currentBackground->getDirection().y);
			} else {
				return;
			}
			
			// MARK: Brick Collisions - Bomb
			if (br->getType() == Tile::Type::Brick_Bomb) {
			// - Compare to all others. Figure out which ones are adjacent.
			// - destroy them.
			for (auto inIter = bricks.begin(); inIter != bricks.end(); ++inIter) {
				auto innerBrick = *inIter;
				if (innerBrick->getRelativePosition().x == br->getRelativePosition().x) {
					if (innerBrick->getRelativePosition().y + 1 == br->getRelativePosition().y || innerBrick->getRelativePosition().y - 1 == br->getRelativePosition().y) {
						innerBrick->destroy();
					}	
				}
				if (innerBrick->getRelativePosition().y == br->getRelativePosition().y) {
					if (innerBrick->getRelativePosition().x + 1 == br->getRelativePosition().x || innerBrick->getRelativePosition().x - 1 == br->getRelativePosition().x) {
						innerBrick->destroy();
					}
				}
			}
			br->destroy();
			return;
		}
			
			br->destroy();
			return;
		}
	}

	// MARK: Wall Collisions
	for (auto iter = walls.begin(); iter != walls.end(); ++iter) {
		auto wl = *iter;
		if (wl->borders().intersects(ball->borders())) {
			if (ball->getPosition().x > 35) {
				ball->setDirection(ball->getDirection().x, -ball->getDirection().y);
				currentBackground->setDirection(currentBackground->getDirection().x, -currentBackground->getDirection().y);
				return;
			} else {
				ball->setDirection(-ball->getDirection().x, ball->getDirection().y);
				currentBackground->setDirection(-currentBackground->getDirection().x, currentBackground->getDirection().y);
				return;
			}
		}
	}
}

void Game::testFunc() {
}