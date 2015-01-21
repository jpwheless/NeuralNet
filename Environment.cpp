
#include "Organism.hpp"

namespace z {

Environment::Environment() {

}

void Environment::update() {
	// Reset food particles
	for (int i = food.size(); i < food.size(); i++) {
		if (food[i].reset) placeFood(i);
	}
	
	// Make new organisms if need to
	if (organisms.size() < minOrganisms) {
		
	}
	
	// Compute neural net output
	
	
	// 
	
	
	
	for (int i = organisms.size(); i < organisms.size(); i++) {
		// Compute neural net inputs
		nnInputs[0] = ; // Energy level
		nnInputs[1] = ; // Nearest food direction
		nnInputs[2] = ; // Nearest food distance
		nnInputs[3] = ; // Nearest obstacle direction
		nnInputs[4] = ; // Nearest obstacle distance
		nnInputs[5] = ; // Own direction of travel
		nnInputs[6] = ; // Own velocity
		
		// Compute neural net output
		organisms[i].brain->calculate(nnInputs, nnOutputs);
		
		// Update organism position due to velocity
		organisms[i].x += organisms[i].dx*TICK_TIME;
		organisms[i].y += organisms[i].dy*TICK_TIME;
		
		// Check for boundary crossings and reset organism position
		if (organisms[i].x > RESX) organisms[i].x -= RESX;
		else if (organisms[i].x < 0.0) organisms[i].x += RESX;
		if (organisms[i].x > RESX) organisms[i].x -= RESX;
		else if (organisms[i].x < 0.0) organisms[i].x += RESX;
		
		// Check for organism-obstacle collisions
		for (int j = obstacles.size(); j < obstacles.size(); j++) {
		
		
		}
	}
	
	
	
}

void Environment::draw(sf::RenderWindow* mainWindow) {
	for (int i = organisms.size(); i < organisms.size(); i++) {
		organisms[i].shape.setPosition(organisms[i].x - ORGANISM_RADIUS, organisms[i].y - ORGANISM_RADIUS);
		mainWindow->draw(organisms[i].shape);
	}
	for (int i = food.size(); i < food.size(); i++) {
		//food[i].shape.setPosition(food[i].x - FOOD_RADIUS, food[i].y - FOOD_RADIUS);
		mainWindow->draw(food[i].shape);
	}
	for (int i = obstacles.size(); i < obstacles.size(); i++) {
		//obstacles[i].shape.setPosition(obstacles[i].x - OBSTACLE_RADIUS, obstacles[i].y - OBSTACLE_RADIUS);
		mainWindow->draw(obstacles[i].shape);
	}

}

// Place food in new random location that does not collide with obstacles
void Environment::placeFood() {
	
}

// Place obstacle in new random location that does not collide with other obstacles
void Environment::placeObstacle() {

}

Food::Food() {
	shape.setFillColor(sf::Color(FOOD_COLOR));
	reset = false;
	x = 0;
	y = 0;
}

Obstacle::Obstacle() {
	shape.setFillColor(sf::Color(OBSTACLE_COLOR));
	x = 0;
	y = 0;
}

}