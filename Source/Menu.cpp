#include "../Include/Menu.hpp"

#include <iostream>

Menu::Menu(sf::RenderWindow& win) : window(win), bounds(0.f, 0.f, window.getDefaultView().getSize().x, window.getDefaultView().getSize().y) {
}

bool Menu::processInput(sf::Event& event) {
	if (event.key.code == sf::Keyboard::Escape) {
		return false;
	}
	return true;
}

bool Menu::update(sf::Time delta) {
	return true;
}

void Menu::render() {
	window.clear(sf::Color::Red);
	window.display();
}