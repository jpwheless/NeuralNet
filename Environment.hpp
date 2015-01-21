#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP


#define DEF_OBSTACLES 10
#define DEF_MIN_ORGANISMS 20
#define DEF_NUM_FOODS 50

#define NET_SHAPE {6,6,6,6}; // Must have 6 inputs and 6 outputs
#define ORGANISM_RADIUS 10;

#define FOOD_RADIUS 5
#define FOOD_COLOR 232,240,86

#define OBSTACLE_RADIUS 20
#define OBSTACLE_COLOR 135,80,7

namespace z {

class Environment {
public:
	int numObstacles;
	int minOrganisms;
	int numFoods;

	std::vector<Organism> organisms;
	std::vector<Food> food;
	std::vector<Obstacle> obstacles;
	std::vector<double> nnInputs(NN_INPUTS, 0.0);
	std::vector<double> nnOutputs(NN_OUTPUTS, 0.0);
	std::vector<int> nnDefaultShape = NN_SHAPE;

	Environment();
	update();
	placeFood(int index);
	
	draw(sf::RenderWindow*);


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