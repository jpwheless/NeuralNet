using namespace z {

Simulation::Simulation() {
	
}

// Create and configure sfgui widgets
void Simulation::initGUI() {
	guiWindow = sfg::Window::Create();
	guiWindow->SetStyle(guiWindow->GetStyle() ^ sfg::Window::TITLEBAR);
	guiWindow->SetStyle(guiWindow->GetStyle() ^ sfg::Window::RESIZE);
}

void Simulation::initSFML() {
	// Match the sfgui and sfml window y dimension
	sf::Vector2f requisition = guiWindow->GetRequisition();
	requisition.y = std::max(RESY, requisition.y);
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
}

void Simulation::launch() {
	initGUI();
	initSFML();
}

void Simulation::draw() {
	sf::Event event;
	
	while (mainWindow->isOpen()) {
				
		elapsedTimeDraw = clockDraw.restart();
		frameRate = FRAMERATE_FILTER*(1.0/elapsedTimeDraw.asSeconds()) + frameRate*(1.0 - FRAMERATE_FILTER);

		// Handle events
		while (mainWindow->pollEvent(event)) {
			guiWindow->HandleEvent(event);
			switch(event.type) {
				case sf::Event::Closed:
					mainWindow->close();
					running = false;
					*threadsPaused = false;
					pauseCV1.notify_one();
					pauseCV2.notify_one();
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
		
		scaleBar->SetFraction(scaleFactor);
		guiWindow->Update(1.0);
		
		mainWindow->clear();
		
		particles->draw(mainWindow);
		input->draw();
		mainWindow->draw(menuDivider, 2, sf::Lines);
					
		// Draw text/gui
		if (statOverlay) {
			std::string temp = std::to_string(scaleFactor);
			temp.resize(4);
			fps.setString(std::to_string((int)frameRateP) + "," + temp + "," + std::to_string((int)frameRateD) + "\n" + 
										std::to_string(*loadBalance1) + "," + std::to_string(*loadBalance2) + "," + std::to_string(*loadBalance3)
										+ "\n" + std::to_string(particles->pSize) + "," + std::to_string(particles->ballAlive)
										+ "\n" + std::to_string(particles->bhV.size()) + "," + std::to_string(particles->bhAlive)
										+ "\n" + std::to_string((int)particles->maxParticleVel));
			mainWindow->draw(fps);
		}
					
		sfguiW.Display(*mainWindow);
		
		// Display drawn objects
		mainWindow->display();
	}
}

void Simulation::logic() {

}


}