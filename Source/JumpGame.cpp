#include "../Include/JumpGame.hpp"

#include <iostream>
#include <random>

template <typename T>
void moveItemToBack(std::vector<T>& v, size_t index) {
	auto it = v.begin() + index;
	std::rotate(it, it + 1, v.end());
}

JumpGame::JumpGame(sf::RenderWindow& win, sf::View& vw): window(win), view(vw), bounds(0.f, 0.f, window.getDefaultView().getSize().x, window.getDefaultView().getSize().y), elapsedProjectileTime(2), corruption(0), gameOver(false) {
	txtManager = std::make_shared<TextureManager>(TextureManager());
	
	window.setView(view);
	buildLevel();
	
	auto ballTile = Tile(0,0,0,Tile::Type::Ball_Default);
	character = std::make_unique<Entity_Ball>(Entity_Ball(ballTile, txtManager));
	character->setPosition(300,212);
	
	auto paddleTile = Tile(0,0,90,Tile::Type::Paddle_Long);
	mirrorPaddle = std::make_unique<Entity_Paddle>(Entity_Paddle(paddleTile, txtManager));
	mirrorPaddle->setPosition(150,15);
	mirrorPaddle->setDirection(0, 70);
	mirrorPaddle->setColor(sf::Color::Magenta);
	
	auto bckTile = Tile(0,0,0, Tile::Type::Background_BrickWall);
	currentBackground = std::make_unique<Entity_Background>(Entity_Background(bckTile, txtManager));
	currentBackground->setScale(320,240);
}

bool JumpGame::processInput(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape) {
			return false;
		} else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
			character->setDirection(-60.f, 0.f);
		} else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
			character->setDirection(60.f, 0.f);
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
	if (gameOver || corruption > 220 || projectiles.size() == 0) {
		return false;
	} else  {
		character->update(delta);
		mirrorPaddle->update(delta);
		flipMirrorPaddle();
		for (auto projectile : projectiles) {
			projectile->update(delta);
		}
		checkCollision();
	
		auto prj_iter = projectiles.begin();
		while (prj_iter != projectiles.end()) {
			auto prj = *prj_iter;
			prj->update(delta);
			if (prj->getDestroyed() == true) {
				prj_iter = projectiles.erase(prj_iter);
			} else {
				++prj_iter;
			}
		}
		fireProjectile(delta);
		return false;
	}
}

void JumpGame::render() {
	window.clear(sf::Color::Black);
	window.draw(*currentBackground);
	window.draw(*character);
	window.draw(*mirrorPaddle);
	for (auto wall : walls) {
		window.draw(*wall);
	}
	for (auto wall : topWalls) {
		window.draw(*wall);
	}
	for (auto projectile : projectiles) {
		window.draw(*projectile);
	}
	window.display();
}

void JumpGame::buildLevel() {
	// MARK - buildLevel() Floor
	std::vector<Tile> floors = {Tile(0, 240, 270, Tile::Type::Wall_Corner_Yellow), Tile(50,240,180, Tile::Type::Wall_Medium_Yellow), Tile(110,240,180, Tile::Type::Wall_Long_Yellow), Tile(130,240,180,Tile::Type::Wall_Short_Yellow), Tile(190,240,180,Tile::Type::Wall_Long_Yellow), Tile(210,240,180,Tile::Type::Wall_Short_Yellow),Tile(270,240,180,Tile::Type::Wall_Long_Yellow), Tile(300,240,180,Tile::Type::Wall_Medium_Yellow), Tile(320, 240, 180, Tile::Type::Wall_Corner_Yellow)};
	for (auto wall : floors) {
		auto wl = std::make_shared<Entity_Wall>(Entity_Wall(wall, 0, txtManager));
		walls.push_back(wl);
	}
	
	// MARK - buildLevel() Top Walls
	std::vector<Tile> tops = {Tile(0,0,0, Tile::Type::Wall_Corner_Yellow), Tile(0,40,270, Tile::Type::Wall_Corner_Yellow), Tile(40,40,180, Tile::Type::Wall_Corner_Yellow),Tile(40,0,90, Tile::Type::Wall_Corner_Yellow), Tile(280,0,0, Tile::Type::Wall_Corner_Yellow), Tile(280,40,270, Tile::Type::Wall_Corner_Yellow), Tile(320,40,180, Tile::Type::Wall_Corner_Yellow),Tile(320,0,90, Tile::Type::Wall_Corner_Yellow)};
	for (auto wall : tops) {
		auto wl = std::make_shared<Entity_Wall>(Entity_Wall(wall, 0, txtManager));
		topWalls.push_back(wl);
	}
	
	// A random number of projectiles
	std::random_device generator;
	std::uniform_int_distribution<int> projectileDistrbution(25,50);
	std::uniform_int_distribution<int> tileDistribution(1,5);
	
	auto capacity = projectileDistrbution(generator);
	while (capacity > 0) {
		auto tileType = tileDistribution(generator);
		Tile t = Tile();
		if (tileType == 1) {
			t.type = Tile::Type::Brick_Basic_Green;
		} else if (tileType == 2) {
			t.type = Tile::Type::Brick_Basic_Red;
		} else if (tileType == 3) {
			t.type = Tile::Type::Brick_Basic_Yellow;
		} else if (tileType == 4) {
			t.type = Tile::Type::Brick_Basic_Blue;
		} else if (tileType == 5) {
			t.type = Tile::Type::Brick_Basic_Purple;
		}
		auto prj = std::make_shared<Entity_Brick>(Entity_Brick(t, txtManager));
		projectiles.push_back(prj);
		--capacity;
	}
}

void JumpGame::checkCollision() {
	// MARK - checkCollision() Projectiles
	for (auto iter = projectiles.begin(); iter != projectiles.end(); ++iter) {
		auto prj = *iter;
		
		if (prj->borders().intersects(character->borders())) {
			prj->destroy();
			return;
		}
		
		if (prj->getPosition().y > 220) {
			increaseCorruption(prj);
			return;
		}
	}
}

void JumpGame::flipMirrorPaddle() {
	if (mirrorPaddle->getPosition().x < 80) {
		mirrorPaddle->invertDirectionX();
	} else if (mirrorPaddle->getPosition().x > 280) {
		mirrorPaddle->invertDirectionX();
	} else {
		return;
	}
}

void JumpGame::fireProjectile(sf::Time delta) {
	if (elapsedProjectileTime > 2) {
		elapsedProjectileTime = 0;
		auto paddlePos = mirrorPaddle->getPosition();
		auto prj = projectiles.front();
		prj->setPosition(paddlePos);
		prj->setDirection(0, 45);
		moveItemToBack(projectiles, 0);
	} else {
		elapsedProjectileTime += delta.asSeconds();
	}
}

void JumpGame::increaseCorruption(std::shared_ptr<Entity_Brick> projectile) {
	// Tile type determines the amount of deterioration.
	if (projectile->getType() == Tile::Type::Brick_Basic_Green) {
		corruption = corruption + 30;
	} else if (projectile->getType() == Tile::Type::Brick_Basic_Red) {
		corruption = corruption + 20;
	} else if (projectile->getType() == Tile::Type::Brick_Basic_Blue) {
		corruption = corruption + 40;	
	} else if (projectile->getType() == Tile::Type::Brick_Basic_Yellow) {
		corruption = corruption + 10;
	} else if (projectile->getType() == Tile::Type::Brick_Basic_Purple) {
		corruption = corruption + 50;
	}
	currentBackground->setPosition(currentBackground->getPosition().x, corruption);
	projectile->destroy();
}