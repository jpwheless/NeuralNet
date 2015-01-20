
#include <SFML/Graphics.hpp>

namespace z {

class Input {
public:
	sf::RenderWindow *mainWindow;
	
	bool windowFocused;
	bool mousePressed;
	bool mouseHeld;
	bool mouseReleased;
	
	Input();
		
	void update();
	void inputWheel(sf::Event &event);
	void draw();

};
}