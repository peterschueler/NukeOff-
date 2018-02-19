#include "../Include/Application.hpp"

const sf::Time Application::secondsFramesRatio = sf::seconds(1.f/60.f);

Application::Application() : window(sf::VideoMode(1280,960), "NukeOut!", sf::Style::Titlebar|sf::Style::Close), view(sf::FloatRect(0,0,320,240)), menuState(window), gameState(window, view) {
	currentState = &menuState;
}

void Application::run() {
	sf::Clock clock;
	sf::Time lastUpdate = sf::Time::Zero;
	while (window.isOpen()) {
		lastUpdate += clock.restart();
		while (lastUpdate > secondsFramesRatio) {
			lastUpdate -= secondsFramesRatio;
			
			processInput();
			update(secondsFramesRatio);
		}
		render();
	}
}

void Application::processInput() {
	sf::Event event;
		while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		} else {
			if (!currentState->processInput(event)) {
				if (currentState == &menuState) {
					currentState = &gameState;
				} else if (currentState == &gameState) {
					currentState = &menuState;
				}
			}
		}
	}
}

void Application::update(sf::Time delta) {
	currentState->update(delta);
}

void Application::render() {
	currentState->render();
}