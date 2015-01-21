#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

#include "NeuralNet.hpp"
#include "definitions.hpp"
#include "rng.hpp"

#define DEF_OBSTACLES 		10
#define DEF_MIN_ORGANISMS 20
#define DEF_NUM_FOODS 		50

#define NET_SHAPE 				{7,7,2} // Must have 7 inputs and 2 outputs
#define ORGANISM_RADIUS 	10

#define FOOD_RADIUS 			5.0
#define FOOD_COLOR 				232,240,86
#define FOOD_ENERGY_VAL 	10.0

#define OBSTACLE_RADIUS 	20.0
#define OBSTACLE_COLOR 		135,80,7

#define MAX_ENERGY 				100.0
#define ACCEL_TO_ENERGY		0.1
#define MAX_VEL 					(MAX_ENERGY/ACCEL_TO_ENERGY)
#define MAX_ACCEL					100.0
#define NN_CALC_COST			0.2*TICK_TIME

#define MAX_SENSE_DIST		250.0
#define THRUST_LINE_RATIO	0.5

namespace z {

class Organism {
public:
	NeuralNet *brain;
	sf::CircleShape shape;
	sf::Vertex thrustLine[2];
	
	uint64_t id;
	double energy;
	double x, y;
	double dx, dy;
	double thrustX, thrustY;
	bool alive;

	Organism(const std::vector<unsigned int> &netShape);
	uint64_t getNewID();
};

class Food {
public:
	sf::CircleShape shape;

	double x, y;
	bool reset;
	
	Food();
};

class Obstacle {
public:
	sf::CircleShape shape;
	
	double x, y;
	
	Obstacle();
};

class Environment {
public:
	sf::RenderWindow *mainWindow;

	int numObstacles;
	int minorganism;
	int numFoods;

	std::vector<Organism> organism;
	std::vector<Food> food;
	std::vector<Obstacle> obstacle;
	std::vector<double> nnInputs;
	std::vector<double> nnOutputs;
	std::vector<unsigned int> nnDefaultShape;

	Environment(sf::RenderWindow* window);
	void update();
	void placeOrganism(Organism &orgToPlace);
	void placeFood(Food &foodToPlace);
	void placeObstacle(Obstacle &obstToPlace);
	
	void draw();

};

}

#endif