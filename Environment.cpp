
#include "Environment.hpp"

namespace z {

Environment::Environment(sf::RenderWindow* window): nnInputs(NN_INPUTS, 0.0), nnOutputs(NN_OUTPUTS, 0.0) {
	mainWindow = window;
	nnDefaultShape = NN_SHAPE;
	for (int i = 0; i < DEF_OBSTACLES; i++) obstacle.push_back(Obstacle());
	for (int i = 0; i < DEF_NUM_FOODS; i++) food.push_back(Food());
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
		organism.push_back(Organism(nnDefaultShape));
		organism.back().brain->randomizeWeights(); // NN weights start out as all zeros
		placeOrganism(organism.back()); //
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
		nnInputs[1] = foodDir/PI2; // Nearest food direction
		nnInputs[2] = std::min(foodDist/MAX_SENSE_DIST, 1.0); // Nearest food distance
		nnInputs[3] = obstacleDir/PI2; // Nearest obstacle direction
		nnInputs[4] = std::min(obstacleDist/MAX_SENSE_DIST, 1.0); // Nearest obstacle distance
		nnInputs[5] = std::atan2(organism[i].dx, organism[i].dy)/PI2; // Own direction of travel
		nnInputs[6] = sqrt(std::pow(organism[i].dx, 2.0) + std::pow(organism[i].dy, 2.0))/MAX_VEL; // Own velocity
		
		// Compute neural net output
		organism[i].brain->calculate(nnInputs, nnOutputs);
		organism[i].energy -= NN_CALC_COST;
		
		// Compute new velocity and energy from NN output
		organism[i].energy -= ACCEL_TO_ENERGY*(MAX_ACCEL*nnOutputs[1]);
		organism[i].thrustX = (MAX_ACCEL*nnOutputs[1])*std::cos(PI2*nnOutputs[1]);
		organism[i].thrustY = (MAX_ACCEL*nnOutputs[1])*std::sin(PI2*nnOutputs[1]);
		organism[i].dx += organism[i].thrustX;
		organism[i].dy += organism[i].thrustY;
		
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

void Environment::draw() {
	for (Organism &orgIndex : organism) {
		orgIndex.shape.setPosition(orgIndex.x - ORGANISM_RADIUS, orgIndex.y - ORGANISM_RADIUS);
		orgIndex.thrustLine[0] = sf::Vertex(sf::Vector2f(orgIndex.x, orgIndex.y));
		orgIndex.thrustLine[1] = sf::Vertex(sf::Vector2f(orgIndex.x - THRUST_LINE_RATIO*orgIndex.thrustX,
																										 orgIndex.y - THRUST_LINE_RATIO*orgIndex.thrustY));
		mainWindow->draw(orgIndex.shape);
		mainWindow->draw(orgIndex.thrustLine, 2, sf::Lines);
	}
	for (Food &foodIndex : food) {
		foodIndex.shape.setPosition(foodIndex.x - FOOD_RADIUS, foodIndex.y - FOOD_RADIUS);
		mainWindow->draw(foodIndex.shape);
	}
	for (Obstacle &obstIndex : obstacle) {
		obstIndex.shape.setPosition(obstIndex.x - OBSTACLE_RADIUS, obstIndex.y - OBSTACLE_RADIUS);
		mainWindow->draw(obstIndex.shape);
	}
}

// Place organism in new random location that does not collide with obstacle
void Environment::placeOrganism(Organism &orgToPlace) {
	bool collision = true;
	double dist;
	double newX, newY;
	int tries = 1;
	
	while (collision && tries <= 30) {
		newX = f::randomUniDist(0.0, RESX);
		newY = f::randomUniDist(0.0, RESY);
	
		collision = false;
		for (Obstacle &obstToCheck : obstacle) {
			dist = sqrt(std::pow(newX - obstToCheck.x, 2.0) + std::pow(newY - obstToCheck.y, 2.0));
			if (dist < ORGANISM_RADIUS + OBSTACLE_RADIUS) collision = true;
		}
		tries++;
		
		if (collision == false) {
			orgToPlace.x = newX;
			orgToPlace.y = newY;
			return;
		}
	}
}

// Place food in new random location that does not collide with obstacle
void Environment::placeFood(Food &foodToPlace) {
	bool collision = true;
	double dist;
	double newX, newY;
	int tries = 1;
	
	while (collision && tries <= 30) {
		newX = f::randomUniDist(0.0, RESX);
		newY = f::randomUniDist(0.0, RESY);
	
		collision = false;
		for (Obstacle &obstToCheck : obstacle) {
			dist = sqrt(std::pow(newX - obstToCheck.x, 2.0) + std::pow(newY - obstToCheck.y, 2.0));
			if (dist < FOOD_RADIUS + OBSTACLE_RADIUS) collision = true;
		}
		tries++;
		
		if (collision == false) {
			foodToPlace.x = newX;
			foodToPlace.y = newY;
			return;
		}
	}
}

// Place obstacle in new random location that does not collide with other obstacle
void Environment::placeObstacle(Obstacle &obstToPlace) {
	bool collision = true;
	double dist;
	double newX, newY;
	int tries = 1;
	
	while (collision && tries <= 30) {
		newX = f::randomUniDist(0.0, RESX);
		newY = f::randomUniDist(0.0, RESY);
	
		collision = false;
		for (Obstacle &obstToCheck : obstacle) {
			if (&obstToCheck != &obstToPlace) { // Don't need to check if the obstacle collides with itself
				dist = sqrt(std::pow(newX - obstToCheck.x, 2.0) + std::pow(newY - obstToCheck.y, 2.0));
				if (dist < 2.0*OBSTACLE_RADIUS) collision = true;
			}
		}
		tries++;
		
		if (collision == false) {
			obstToPlace.x = newX;
			obstToPlace.y = newY;
			return;
		}
	}
}

// ======================================== Subclass functions ========================================

Organism::Organism(const std::vector<unsigned int> &netShape) : shape(2.0*ORGANISM_RADIUS, 30) {
	brain = new NeuralNet(netShape);
	id = getNewID();
	x = 0.0;
	y = 0.0;
	dx = 0.0;
	dy = 0.0;
	thrustX = 0.0;
	thrustY = 0.0;
	alive = true;
	
	int r = f::randomUniDist(0.0, 256.0);
	int g = f::randomUniDist(0.0, 256.0);
	int b = f::randomUniDist(0.0, 256.0);
	shape.setFillColor(sf::Color(r, g, b));
}

// Returns a uique identifier number
uint64_t Organism::getNewID() {
	static uint64_t idCounter = 0;
	
	return idCounter++;
}

Food::Food() : shape(2.0*FOOD_RADIUS, 4) {
	shape.setFillColor(sf::Color(FOOD_COLOR));
	reset = false;
	x = 0;
	y = 0;
}

Obstacle::Obstacle() : shape(2.0*OBSTACLE_RADIUS, 4) {
	shape.setFillColor(sf::Color(OBSTACLE_COLOR));
	x = 0;
	y = 0;
}

}