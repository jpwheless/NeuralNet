#ifndef ORGANISM_HPP
#define ORGANISM_HPP

#include "NeuralNet.hpp"

namespace z {

class Organism {
public:
	uint64_t id;
	NeuralNet *brain;
	
	unsigned int energy;
	double x, y;
	double dx, dy;

	Organism(const std::vector<unsigned int> &netShape);
	
	uint64_t getNewID();
};

}

#endif