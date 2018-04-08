#include "../Include/TextGame.hpp"

TextGame::TextGame(sf::RenderWindow& win, sf::View& vw) : window(win), view(vw) {
	txtManager = std::make_shared<TextureManager>(TextureManager());
	
	window.setView(view);
}

bool TextGame::processInput(sf::Event& event) {
	return true;
}

ExitState TextGame::update(sf::Time delta) {
	if (gameOver) {
		return ExitState::GameOver;
	} else {
		return ExitState::Running;
	}
}

void TextGame::render() {
	window.clear(sf::Color::Black);
	window.display();
}

void TextGame::resetNuke() {
}