#include "../Include/JumpGame.hpp"

JumpGame::JumpGame(sf::RenderWindow& win, sf::View& vw): window(win), view(vw), bounds(0.f, 0.f, window.getDefaultView().getSize().x, window.getDefaultView().getSize().y), gameOver(false) {
	txtManager = std::make_shared<TextureManager>(TextureManager());
	
	window.setView(view);
	buildLevel();
	
	auto ballTile = Tile(0,0,0,Tile::Type::Ball_Default);
	character = std::make_unique<Entity_Ball>(Entity_Ball(ballTile, txtManager));
	character->setPosition(300,212);
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
	if (gameOver) {
		return false;
	}
	character->update(delta);
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
}

void JumpGame::render() {
	window.clear(sf::Color::Black);
	window.draw(*character);
	for (auto wall : walls) {
		window.draw(*wall);
	}
	for (auto projectile : projectiles) {
		window.draw(*projectile);
	}
	window.display();
}

void JumpGame::buildLevel() {
	std::vector<Tile> floors = {Tile(0, 240, 270, Tile::Type::Wall_Corner_Yellow), Tile(50,240,180, Tile::Type::Wall_Medium_Yellow), Tile(110,240,180, Tile::Type::Wall_Long_Yellow), Tile(130,240,180,Tile::Type::Wall_Short_Yellow), Tile(190,240,180,Tile::Type::Wall_Long_Yellow), Tile(210,240,180,Tile::Type::Wall_Short_Yellow),Tile(270,240,180,Tile::Type::Wall_Long_Yellow), Tile(300,240,180,Tile::Type::Wall_Medium_Yellow), Tile(320, 240, 180, Tile::Type::Wall_Corner_Yellow)};
	for (auto wall : floors) {
		auto wl = std::make_shared<Entity_Wall>(Entity_Wall(wall, 0, txtManager));
		walls.push_back(wl);
	}
	Tile t = Tile();
	t.type = Tile::Type::Brick_Basic_Green;
	auto prj = std::make_shared<Entity_Brick>(Entity_Brick(t, txtManager));
	prj->setPosition(200, -20);
	prj->setDirection(0, 20);
	projectiles.push_back(prj);
}

void JumpGame::checkCollision() {
	for (auto iter = projectiles.begin(); iter != projectiles.end(); ++iter) {
		auto prj = *iter;
		
		if (prj->borders().intersects(character->borders())) {
			prj->destroy();
			return;
		}
	}
}