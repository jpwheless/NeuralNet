#include "Input.hpp"

namespace z {

Input::Input(sf::RenderWindow* window) {
	mainWindow = window;
	windowFocused = true; // Probably true, but no way to know
	mousePressed = false;
	mouseHeld = false;
	mouseReleased = false;
}


void Input::update() {

}

void Input::inputWheel(sf::Event &event) {

}

void Input::draw() {

}

}