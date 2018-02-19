#include "../Include/JumpGame.hpp"

JumpGame::JumpGame(sf::RenderWindow& win, sf::View& vw): window(win), view(vw), bounds(0.f, 0.f, window.getDefaultView().getSize().x, window.getDefaultView().getSize().y), gameOver(false) {
	txtManager = std::make_shared<TextureManager>(TextureManager());
	
	window.setView(view);
	buildLevel();
}

bool JumpGame::processInput(sf::Event& event) {
	return true;
}

bool JumpGame::update(sf::Time delta) {
	if (gameOver) {
		return false;
	}
}

void JumpGame::render() {
	window.clear(sf::Color::Black);
	window.display();
}

void JumpGame::buildLevel() {
}