#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

#include "definitions.hpp"

using namespace z {

class Simulation {
private:
	// Stat overlay objects
	sf::Font calibri;
	sf::Text fps;
	bool statOverlay;
	
	bool running;
	
	// SFGUI objects
	sfg::SFGUI sfguiW;
	sfg::Window::Ptr guiWindow;
	
	// Timekeeping objects
	sf::Clock clockLogic;
	sf::Time elapsedTimeLogic;
	sf::Clock clockDraw;
	sf::Time elapsedTimeDraw;
	double frameRate, logicRate
	
	// Threads
	std::thread* drawThread;
	std::thread* logicThread;
	std::atomic<bool>* logicPaused = new std::atomic<bool>;

public:
	sf::RenderWindow *mainWindow;
	z::Input *input;

	Simulation();
	void initGUI();
	void initSFML(); // Call after initGUI()
	void launch();
	void draw();
	void logic();

};

}