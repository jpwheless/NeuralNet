#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <algorithm>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

#include "Input.hpp"

#define FRAMERATE_FILTER 0.05

namespace z {

static std::mutex pauseMutex;
static std::condition_variable pauseCV;

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
	double frameRate, logicRate;
	
	// Threads
	std::thread* drawThread;
	std::thread* logicThread;
	std::atomic<bool> *logicPaused = new std::atomic<bool>;
	std::atomic<bool> *logicVSynced = new std::atomic<bool>;

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

#endif