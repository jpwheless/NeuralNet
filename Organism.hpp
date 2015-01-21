#ifndef ORGANISM_HPP
#define ORGANISM_HPP

#include <SFML/Graphics.hpp>
#include "NeuralNet.hpp"

namespace z {

class Organism {
public:
	NeuralNet *brain;
	sf::CircleShape circle;
	
	uint64_t id;
	unsigned int energy;
	double x, y;
	double dx, dy;

	Organism(const std::vector<unsigned int> &netShape);
	uint64_t getNewID();
};

}

#endif