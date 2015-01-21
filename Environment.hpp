#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Organism.hpp"
#include "NeuralNet.hpp"
#include "definitions.hpp"
#include "rng.hpp"

#define DEF_OBSTACLES 		10
#define DEF_MIN_ORGANISMS 20
#define DEF_NUM_FOODS 		50

#define NET_SHAPE 				{6,6,6,6}; // Must have 6 inputs and 6 outputs
#define ORGANISM_RADIUS 	10;

#define FOOD_RADIUS 			5.0
#define FOOD_COLOR 				232,240,86
#define FOOD_ENERGY_VAL 	10.0

#define OBSTACLE_RADIUS 	20.0
#define OBSTACLE_COLOR 		135,80,7

#define MAX_ENERGY 				100.0
#define ACCEL_TO_ENERGY		0.1
#define MAX_VEL 					(MAX_ENERGY*ENERGY_TO_ACCEL)
#define MAX_ACCEL					100.0
#define NN_CALC_COST			0.2*TICK_TIME

#define MAX_SENSE_DIST		250.0

namespace z {

class Environment {
public:
	int numObstacles;
	int minorganism;
	int numFoods;

	std::vector<Organism> organism;
	std::vector<Food> food;
	std::vector<Obstacle> obstacle;
	std::vector<double> nnInputs(NN_INPUTS, 0.0);
	std::vector<double> nnOutputs(NN_OUTPUTS, 0.0);
	std::vector<int> nnDefaultShape = NN_SHAPE;

	Environment();
	update();
	placeFood(int index);
	
	draw(sf::RenderWindow*);

};

class Organism {
public:
	NeuralNet *brain;
	sf::CircleShape circle;
	
	uint64_t id;
	double energy;
	double x, y;
	double dx, dy;

	Organism(const std::vector<unsigned int> &netShape);
	uint64_t getNewID();
};

class Food {
public:
	sf::CircleShape shape(2*FOOD_RADIUS, 4);

	double x, y;
	bool reset;
	
	Food();
};

class Obstacle {
public:
	sf::CircleShape shape(2*OBSTACLE_RADIUS, 8);

	double x, y;
	
	Obstacle();
}

}

#endif