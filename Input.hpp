#ifndef INPUT_HPP
#define INPUT_HPP

#include <SFML/Graphics.hpp>

namespace z {

class Input {
public:
	sf::RenderWindow *mainWindow;
	
	bool windowFocused;
	bool mousePressed;
	bool mouseHeld;
	bool mouseReleased;
	
	Input(sf::RenderWindow* window);
		
	void update();
	void inputWheel(sf::Event &event);
	void draw();

};
}

#endif