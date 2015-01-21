#include "Simulation.hpp"
#include "definitions.hpp"

namespace z {

Simulation::Simulation() {
	input = new z::Input();
}

// Create and configure sfgui widgets
void Simulation::initGUI() {
	guiWindow = sfg::Window::Create();
	guiWindow->SetStyle(guiWindow->GetStyle() ^ sfg::Window::TITLEBAR);
	guiWindow->SetStyle(guiWindow->GetStyle() ^ sfg::Window::RESIZE);
	
	guiWindow->SetPosition(sf::Vector2f(RESX, 0));
}

void Simulation::initSFML() {
	// Match the sfgui and sfml window y dimension
	sf::Vector2f requisition = guiWindow->GetRequisition();
	double temp = requisition.y;
	requisition.y = std::max(RESY, temp);
	guiWindow->SetRequisition(requisition);
	
	mainWindow = new sf::RenderWindow(sf::VideoMode(RESX + requisition.x, RESY), 
		"Particles!", sf::Style::Titlebar|sf::Style::Close, 
		sf::ContextSettings(24, 8, 8, 3, 0)); // Set openGL parameters
	
	mainWindow->setVerticalSyncEnabled(true);
	
	// Input needs the mainWindow pointer to function
	input->mainWindow = mainWindow;
	
	// Load font from system font folder directory
	// For use in main window stat overlay
	char* windir = std::getenv("windir");
	if (windir) {
		std::string windirS(windir);
		if(calibri.loadFromFile(windirS + "\\fonts\\calibri.ttf")) {
			statOverlay = true;
			fps.setFont(calibri);
			fps.setCharacterSize(15);
			fps.setColor(sf::Color::White);
		}
	}
	
	mainWindow->setActive(false); // Must be deactivated here before it can be activated in the draw thread
}

void Simulation::launch() {
	initGUI();
	initSFML();
	
	running = true;
	*logicPaused = false;
	*logicVSynced = true;
	
	drawThread = new std::thread(&Simulation::draw, this);
	logicThread = new std::thread(&Simulation::logic, this);
	
	// Jumpstart framerates to their expected value
	frameRate = 60;
	logicRate = 60;
	
	clockLogic.restart();
	clockDraw.restart();
					
	drawThread->join();
	logicThread->join();
}

void Simulation::draw() {
	mainWindow->setActive(true);

	sf::Event event;
	
	while (mainWindow->isOpen()) {
				
		elapsedTimeDraw = clockDraw.restart();
		frameRate = FRAMERATE_FILTER*(1.0/elapsedTimeDraw.asSeconds()) + frameRate*(1.0 - FRAMERATE_FILTER);

		// Handle events
		while (mainWindow->pollEvent(event)) {
			guiWindow->HandleEvent(event);
			switch(event.type) {
				case sf::Event::Closed:
					running = false;
					*logicPaused = false;
					*logicVSynced = false;
					pauseCV.notify_one();
					mainWindow->close();
					break;
				case sf::Event::LostFocus:
					input->windowFocused = false;
					break;
				case sf::Event::GainedFocus:
					input->windowFocused = true;
					break;
				case sf::Event::MouseWheelMoved:
					input->inputWheel(event);
					break;
				case sf::Event::MouseButtonReleased:
					if (event.mouseButton.button == sf::Mouse::Left) input->mouseReleased = true;
					break;
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left) input->mousePressed = true;
					break;
				default:
					break;
			}
		}
								
		input->update();
		
		guiWindow->Update(1.0);
		
		mainWindow->clear();
		
		// Draw organisms here
		
		input->draw();
					
		// Draw text/gui
		if (statOverlay) {
			fps.setString(std::to_string((int)frameRate) + "," + std::to_string((int)logicRate));
			mainWindow->draw(fps);
		}
					
		sfguiW.Display(*mainWindow);
		
		// Display drawn objects
		mainWindow->display();
		
		// If vsync for logic is enabled, and logic is not paused, tell logic to calculate again.
		if (*logicVSynced && !(*logicPaused)) {
			pauseCV.notify_one();
		}
	}
}

void Simulation::logic() {
	std::unique_lock<std::mutex> lock(pauseMutex);

	while(running){
		if (*logicPaused || *logicVSynced) {
			pauseCV.wait(lock);
			clockLogic.restart();
		}
	
		// Do calculations here.
		
		elapsedTimeLogic = clockLogic.restart();
		logicRate = FRAMERATE_FILTER*(1.0/elapsedTimeLogic.asSeconds()) + logicRate*(1.0 - FRAMERATE_FILTER);
	}
}


}