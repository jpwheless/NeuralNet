
#include "Environment.hpp"

namespace z {

Environment::Environment() {

}

void Environment::update() {
	double dist;
	double obstacleDist;
	double foodDist;
	double obstacleDir;
	double foodDir;
	int jTmp;
	
	// Reset food particles
	for (Food &index : food) {
		if (index.reset) placeFood(index);
	}
	
	// Make new random organism if need to
	if (organism.size() < minorganism) {
		
	}
	
	
	for (int i = organism.size(); i < organism.size(); i++) {
		// Find nearest obstacle
		jTmp = 0;
		obstacleDist = 0.0;
		for (int j = obstacle.size(); j < obstacle.size(); j++) {
			dist = sqrt(std::pow(organism[i].x - obstacle[j].x, 2.0) + std::pow(organism[i].y - obstacle[j].y, 2.0));
			if (dist < obstacleDist) {
				obstacleDist = dist;
				jTmp = j;
			}
		}
		obstacleDir = std::atan2(obstacle[jTmp].x - organism[i].x, obstacle[jTmp].y - organism[i].y);
	
		// Find nearest food
		jTmp = 0;
		foodDist = 0.0;
		for (int j = food.size(); j < food.size(); j++) {
			dist = sqrt(std::pow(organism[i].x - food[j].x, 2.0) + std::pow(organism[i].y - food[j].y, 2.0));
			if (dist < foodDist) {
				foodDist = dist;
				jTmp = j;
			}
		}
		foodDir = std::atan2(food[jTmp].x - organism[i].x, food[jTmp].y - organism[i].y);
		
		// Check for organism-obstacle collisions
		if (obstacleDist < OBSTACLE_RADIUS) organism[i].alive = false;
		
		// Check for food collisions
		if (foodDist < OBSTACLE_RADIUS) {
			organism[i].energy += FOOD_ENERGY_VAL;
			food[jTmp].reset = true;
		}
		
		// Compute neural net inputs
		nnInputs[0] = std::min(organism[i].energy/MAX_ENERGY, 1.0); // Energy level
		nnInputs[1] = ; // Nearest food direction
		nnInputs[2] = std::min(foodDist/MAX_SENSE_DIST, 1.0); // Nearest food distance
		nnInputs[3] = ; // Nearest obstacle direction
		nnInputs[4] = std::min(obstacleDist/MAX_SENSE_DIST, 1.0); // Nearest obstacle distance
		nnInputs[5] = ; // Own direction of travel
		nnInputs[6] = ; // Own velocity
		
		// Compute neural net output
		organism[i].brain->calculate(nnInputs, nnOutputs);
		organism[i].energy -= NN_CALC_COST;
		
		// Compute new velocity and energy from NN output
		organism[i].energy -= ACCEL_TO_ENERGY*(MAX_ACCEL*nnOutputs[1]);
		organism[i].dx += (MAX_ACCEL*nnOutputs[1])*std::cos(PI2*nnOutputs[1]);
		organism[i].dy += (MAX_ACCEL*nnOutputs[1])*std::sin(PI2*nnOutputs[1]);
		
		// Check if enough energy to continue operating
		if (organism[i].energy < 0.0) organism[i].alive = false;
		
		if (organism[i].alive) {
			// Update organism position due to velocity
			organism[i].x += organism[i].dx*TICK_TIME;
			organism[i].y += organism[i].dy*TICK_TIME;
			
			// Check for boundary crossings and reset organism position
			if (organism[i].x > RESX) organism[i].x -= RESX;
			else if (organism[i].x < 0.0) organism[i].x += RESX;
			if (organism[i].y > RESY) organism[i].y -= RESY;
			else if (organism[i].y < 0.0) organism[i].y += RESY;
			
		}
		else { // Delete dead organism
			std::swap(organism[i],organism.back());
			organism.pop_back();
			i--;
		}
	}
}

void Environment::draw(sf::RenderWindow* mainWindow) {
	for (int i = organism.size(); i < organism.size(); i++) {
		organism[i].shape.setPosition(organism[i].x - ORGANISM_RADIUS, organism[i].y - ORGANISM_RADIUS);
		mainWindow->draw(organism[i].shape);
	}
	for (int i = food.size(); i < food.size(); i++) {
		//food[i].shape.setPosition(food[i].x - FOOD_RADIUS, food[i].y - FOOD_RADIUS);
		mainWindow->draw(food[i].shape);
	}
	for (int i = obstacle.size(); i < obstacle.size(); i++) {
		//obstacle[i].shape.setPosition(obstacle[i].x - OBSTACLE_RADIUS, obstacle[i].y - OBSTACLE_RADIUS);
		mainWindow->draw(obstacle[i].shape);
	}

}

// ======================================== Subclass functions ========================================

Organism::Organism(const std::vector<unsigned int> &netShape) {
	brain = new NeuralNet(netShape);
	id = getNewID();
}

// Returns a uique identifier number
uint64_t Organism::getNewID() {
	static uint64_t idCounter = 0;
	
	return idCounter++;
}

// Place food in new random location that does not collide with obstacle
void Environment::placeFood(Food &food) {
	bool collision = true;
	double dist;
	double newX, newY;
	
	while (collision) {
		newX = f::randomUniDist(0.0, RESX);
		newY = f::randomUniDist(0.0, RESY);
	
		collision = false;
		for (obstacle &index : obstacle) {
			dist = sqrt(std::pow(organism[i].x - obstacle[j].x, 2.0) + std::pow(organism[i].y - obstacle[j].y, 2.0));
			if (dist < FOOD_RADIUS + OBSTACLE_RADIUS) collision = true;
		}
	
	}
}

// Place obstacle in new random location that does not collide with other obstacle
void Environment::placeObstacle(Obstacle &food) {
	
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