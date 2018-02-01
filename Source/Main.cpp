#include "../Include/Application.hpp"

#include <iostream>

int main() {
	try {
		Application app;
		app.run();
	} catch (std::exception& e) {
		std::cout << "\nNuke Out failed. This is why: " << e.what() << std::endl;
	}
}